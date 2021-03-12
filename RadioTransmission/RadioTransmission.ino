#define DATA_PIN 2
#define LED_PIN 4

void setup(){
    pinMode(LED_PIN, OUTPUT);
    pinMode(DATA_PIN, INPUT);
}

void loop() {
    digitalWrite(LED_PIN, digitalRead(DATA_PIN));
}
