
// This script is meant to test methods to transfer data between the control app and the robot
// It uses HTTP requests over Ethernet because I still have trouble making the Wifi board work

#include <Ethernet.h>

//Ethernet shield address
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xA5, 0x7E };
IPAddress ip(192, 168, 1, 28);
EthernetServer server(4200);

void setup()
{
  Serial.begin(9600);

  char erreur = 0;
  erreur = Ethernet.begin(mac); // On démarre le shield Ethernet SANS adresse ip (donc donnée via DHCP)

  // si une erreur a eu lieu cela signifie que l'attribution DHCP
  // ne fonctionne pas. On initialise donc en forçant une IP
  if (erreur == 0)
    Ethernet.begin(mac, ip);

  // Donne une seconde au shield pour s'initialiser
  delay(1000);

  server.begin();
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
