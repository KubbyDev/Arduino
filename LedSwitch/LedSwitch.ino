#include <SPI.h>
#include <Ethernet.h>

// Code fortement inspire de https://zestedesavoir.com/tutoriels/686/arduino-premiers-pas-en-informatique-embarquee/1213_internet-of-things-arduino-sur-internet/4848_arduino-et-ethernet-serveur/

//Adresse du Ethernet Shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xA5, 0x7E };
IPAddress ip(192, 168, 1, 28);
EthernetServer serveur(4200);

char *url = (char *)malloc(100); // L'url recu à stocker
boolean etats[3] = {LOW, LOW, LOW}; // L'état des 3 sorties

void setup()
{
  // On démarre la voie série pour déboguer
  Serial.begin(9600);

  // Configure et initialise les broches
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

  char erreur = 0;
  erreur = Ethernet.begin(mac); // On démarre le shield Ethernet SANS adresse ip (donc donnée via DHCP)

  // si une erreur a eu lieu cela signifie que l'attribution DHCP
  // ne fonctionne pas. On initialise donc en forçant une IP
  if (erreur == 0)
    Ethernet.begin(mac, ip);

  // Donne une seconde au shield pour s'initialiser
  delay(1000);

  serveur.begin();
}

void loop() {

  // Regarde si un client est connecté et attend une réponse
  EthernetClient client = serveur.available();

  if (client) { // Un client est là ?

    char *url = (char *)malloc(100); //L'url recue (remplie au fur et a mesure)
    int index = 0;

    while (client.connected()) {

      if (client.available()) {

        char newChar = client.read();
        if (newChar == '\n' || index > 100) { //Si on a fini la lecture on fait le traitement

          digitalWrite(3, readRequest(url));
          respond(client);
          
          break; //On sort du while
        }
        else { //Sinon on continue la lecture

          url[index] = newChar;
          index += 1;
        }
      }
    }

    // Ferme la connexion avec le client
    client.stop();
  }
}

boolean readRequest(char request[]) {

  int i = 0;
  while (! (request[i] == 'b' && request[i + 1] == '=')) //Tant qu'on est pas arrive a b=
    i += 1;

  //Une fois qu'on est a b=, on regarde ce qu'il y a juste apres
  return request[i + 2] == '3';
}

void respond(EthernetClient client) {

  //Header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Access-Control-Allow-Origin: *");
  client.println();

  //Body
  client.println("{");
  
  client.print("\t\"uptime\": ");
  client.print(millis());
  
  client.println(",");

  client.print("\t\"3\": ");
  client.print(digitalRead(3));
  
  client.println("}");
}
