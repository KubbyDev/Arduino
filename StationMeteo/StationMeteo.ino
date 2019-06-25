

//J'ai pas reussi a faire marcher le capteur de pression :'(



//Pression
#include <SFE_BMP180.h>
#include <Wire.h>

//Humidite
#include <dht.h>

//Connection
#include <SPI.h>
#include <Ethernet.h>

//Adresse du Ethernet Shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xA5, 0x7E };
IPAddress ip(192, 168, 1, 28);

//DIGITAL
byte SOUND_PIN = 2;
byte HUMIDITY_PIN = 7;
byte TEMPERATURE_PIN = 12;

//ANALOG
byte WATER_PIN = A1;
byte LUMINOSITY_PIN = A2;
byte SMOKE_PIN = A0;
byte PRESSURE1_PIN = A4;
byte PRESSURE2_PIN = A5;

dht humiditySensor;
SFE_BMP180 bmp180;

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
  
  if (bmp180.begin() == 0) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    //while (1);
  }
  else {
    bmp180.startTemperature();
    bmp180.startPressure(3);
  }
  
  connect();

  Serial.println("connected");

  delay(2000);

}

void connect() {

  char erreur = 0;
  erreur = Ethernet.begin(mac); // On démarre le shield Ethernet SANS adresse ip (donc donnée via DHCP)

  // si une erreur a eu lieu cela signifie que l'attribution DHCP
  // ne fonctionne pas. On initialise donc en forçant une IP
  if (erreur == 0)
    Ethernet.begin(mac, ip);
  
}

void loop() {    

  bool sound = analogRead(SOUND_PIN);
  
  int humidity;
  if(humiditySensor.read11(HUMIDITY_PIN) != 0)
    humidity = humiditySensor.humidity;

  double T;
  double pressure;
  bmp180.getTemperature(T);
  bmp180.getPressure(pressure, T);
  int altitude;// = bme.readAltitude(SEALEVELPRESSURE_HPA);
  bmp180.startTemperature();
  bmp180.startPressure(3);

  int smoke = analogRead(SMOKE_PIN);

  int luminosity = analogRead(LUMINOSITY_PIN);

  int temperature = analogRead(TEMPERATURE_PIN);

  int water = analogRead(WATER_PIN);

  Serial.print("sound ");Serial.println(sound);  
  Serial.print("humidity ");Serial.println(humidity);
  Serial.print("pressure ");Serial.println(pressure);
  Serial.print("altitude ");Serial.println(altitude);
  Serial.print("smoke ");Serial.println(smoke);
  Serial.print("luminosity ");Serial.println(luminosity);
  Serial.print("temperature ");Serial.println(temperature);
  Serial.print("water ");Serial.println(water);

  String data = String(
                "sound=" + String(sound) + "&"
              + "humidity=" + String(humidity) + "&"
              + "pressure=" + String(pressure) + "&"
              + "altitude=" + String(altitude) + "&"
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
  
  delay(5000);
  Serial.println();
  Serial.println();

}
