int firstPin = 2;
int pinsNumber = 4;

int buzzerPin = 11; 
int pin = 13;

void setup() {

  pinMode(pin, INPUT);

  for(int i = firstPin; i < firstPin+pinsNumber; i++)
    pinMode(i, OUTPUT);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);
}

void loop() {
  
  int buttonState = digitalRead(pin);

  if(buttonState == HIGH) {
     digitalWrite(buzzerPin, LOW);   
     loupiottes();
  }
  else
    digitalWrite(buzzerPin, HIGH);
}

void loupiottes() {

  digitalWrite(firstPin, HIGH);
  delay(100);
  
  for(int i = firstPin; i < firstPin+pinsNumber -1; i++) {
    digitalWrite(i, LOW);
    digitalWrite(i+1, HIGH);
    delay(100);
  }
  
  digitalWrite(firstPin+pinsNumber-1, LOW);
  
  delay(100);
  
}
