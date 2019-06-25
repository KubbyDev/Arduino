#include <Servo.h>
 
const byte SERVO_PIN = 14; //analog pin 0
const byte TRIGGER_PIN = 2;
const byte ECHO_PIN = 4;
const int MEASURE_TIMEOUT = 3000; // 6ms = ~1m a 340m/s aller retour
const float SOUND_SPEED = 340.0 / 1000; //en mm/us

Servo servo;
int angle = 1;
bool invertDirection = false;

void setup() {

  pinMode(14,OUTPUT);
  servo.attach(14); 

  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(115200);
  Serial.println("Ready");

}

void loop() {

  //Lancement de la mesure
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  //Mesure
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT); //Blocking (~5ms)
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  
  delay(10);

  Serial.println(measure);

  //Rotation du servo
  if(angle >= 180 || angle <= 0)
    invertDirection = !invertDirection;
  angle += (invertDirection) ? -1 : 1;  
  servo.write(angle);

/*
  // Fait bouger le bras de 0° à 180°
  for (int position = 0; position <= 180; position++) {
    servo.write(position);
    delay(15);
  }
  
  // Fait bouger le bras de 180° à 10°
  for (int position = 180; position >= 0; position--) {
    servo.write(position);
    delay(15);
  }
  */
}
