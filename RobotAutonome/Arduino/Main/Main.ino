int pin = 2;

void setup() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  Serial.begin(9600);
}

void loop() {
  int i = Serial.read();
  if(i != -1 && i != 10) {
    Serial.println(i);
    if(i == '1')
      digitalWrite(pin, HIGH);
    else
      digitalWrite(pin, LOW);
  }
}
