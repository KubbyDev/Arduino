#include <SFE_BMP180.h>  //Pression
#include <Wire.h>
#include <dht.h>         //Humidite
#include <SPI.h>         //Connection
#include <Ethernet.h>

//Adresse du Ethernet Shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xA5, 0x7E };
IPAddress ip(192, 168, 1, 28);
EthernetServer server(4300);

//Pins
byte SOUND_PIN = 2;
byte HUMIDITY_PIN = 7;
byte TEMPERATURE_PIN = 12;
byte WATER_PIN = A1;
byte LUMINOSITY_PIN = A2;
byte SMOKE_PIN = A0;
byte PRESSURE1_PIN = A4;
byte PRESSURE2_PIN = A5;

//Outils
dht humiditySensor;
SFE_BMP180 bmp180;

//Valeurs
int sound;
int humidity;
int pressure;
int altitude;
int smoke;
int luminosity;
int temperature;
int water;

//SETUP
void setup() {

  Serial.begin(9600);

  pinMode(SOUND_PIN, INPUT);
  pinMode(HUMIDITY_PIN, INPUT);
  pinMode(TEMPERATURE_PIN, INPUT);
  pinMode(WATER_PIN, INPUT);
  pinMode(LUMINOSITY_PIN, INPUT);
  pinMode(SMOKE_PIN, INPUT);
  pinMode(PRESSURE1_PIN, INPUT);
  pinMode(PRESSURE2_PIN, INPUT);

  Serial.println("begin");

  //Marche pas
  //Initialisation du capteur de pression
  if (bmp180.begin() == 0) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    //while (1);
  }
  else {
    bmp180.startTemperature();
    bmp180.startPressure(3);
  }

  //Connexion par Ethernet
  char erreur = 0;
  erreur = Ethernet.begin(mac); // On démarre le shield Ethernet SANS adresse ip (donc donnée via DHCP)
  // si une erreur a eu lieu cela signifie que l'attribution DHCP
  // ne fonctionne pas. On initialise donc en forçant une IP
  if (erreur == 0)
    Ethernet.begin(mac, ip);

  Serial.println("connected");

  server.begin();

  //Permet d'etre sur que tout est pret
  delay(2000);

}

//LOOP
void loop() {

  EthernetClient client = server.available();
  if (client) { // Si un client est connecte

    //On ecoute pas ce qu'il a a dire parce qu'on s'en fous
    //On lui repond
    readValues();
    sendValuesViaResponse(client);

    //On attend un peu et on ferme la connexion
    delay(10);
    client.stop();
  }

  delay(100);
}

//Lis les valeurs des capteurs et les passe dans les variables globales (Valeurs)
void readValues() {    

  sound = analogRead(SOUND_PIN);
  
  if(humiditySensor.read11(HUMIDITY_PIN) != 0)
    humidity = humiditySensor.humidity;

  double T;
  double P;
  bmp180.getTemperature(T);
  bmp180.getPressure(P, T);
  int altitude;// = bme.readAltitude(SEALEVELPRESSURE_HPA);
  bmp180.startTemperature();
  bmp180.startPressure(3);
  pressure = P;

  smoke = analogRead(SMOKE_PIN);

  luminosity = analogRead(LUMINOSITY_PIN);

  temperature = analogRead(TEMPERATURE_PIN);

  water = analogRead(WATER_PIN);

}

//Envoie les valeurs au serveur en reponse a un Get
void sendValuesViaResponse(EthernetClient client) {

  Serial.println("Response");

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Access-Control-Allow-Origin: *");
  client.println();

  client.print(sound);
  client.print(",");
  client.print(humidity);
  client.print(",");
  client.print(pressure);
  client.print(",");
  client.print(altitude);
  client.print(",");
  client.print(smoke);
  client.print(",");
  client.print(luminosity);
  client.print(",");
  client.print(temperature);
  client.print(",");
  client.print(water);
  
}

//Envoie les valeurs au serveur en lui balancant un Get sans prendre en compte la reponse
void sendValuesViaGet() {

  String data = String(
                "sound=" + String(sound) + "&"
              + "humidity=" + String(humidity) + "&"
              + "pressure=" + String(pressure) + "&"   //Marche pas
              + "altitude=" + String(altitude) + "&"   //Marche pas
              + "smoke=" + String(smoke) + "&"
              + "luminosity=" + String(luminosity) + "&"
              + "temperature=" + String(temperature) + "&"
              + "water=" + String(water)
              );             
  Serial.println(data);

  EthernetClient client;
  if(client.connect("192.168.1.16", 3200)) {
    client.print("GET /meteo/?");
    client.print(data);
    client.println(" HTTP/1.1");
    client.println("Host: 192.168.1.16:3200");
    client.println("Connection: close");
    client.println();
  }
  else
    Serial.println("Erreur de connection");

  client.stop();

}
