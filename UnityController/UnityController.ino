int frontPin = 2;
int backPin = 3;
int rightPin = 5;
int leftPin = 6;

int buttonJPin = 8;
int buttonAPin = 9;
int buttonBPin = 11;
int buttonCPin = 12;

int prevForward = 1;
int prevRight = 1;
bool prevA = false;
bool prevB = false;
bool prevC = false;
bool prevJ = false;

void setup() {

  pinMode(frontPin, INPUT);
  pinMode(backPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(buttonJPin, INPUT);
  pinMode(buttonAPin, INPUT);
  pinMode(buttonBPin, INPUT);
  pinMode(buttonCPin, INPUT);

  Serial.begin(9600);
}

void loop() {

  //Lecture des entrees
  
  //Boutons
  bool a = digitalRead(buttonAPin) == HIGH;
  bool b = digitalRead(buttonBPin) == HIGH;
  bool c = digitalRead(buttonCPin) == HIGH;
  bool j = digitalRead(buttonJPin) == HIGH;
  
  //Joystick vertical (0 => negatif, 1 => neutre, 2 => positif)
  int forwardAxis = 1;
  if(digitalRead(frontPin) == HIGH)
    forwardAxis++;
  if(digitalRead(backPin) == HIGH)
    forwardAxis--;
    
  //Joystick horizontal (0 => negatif, 1 => neutre, 2 => positif)
  int rightAxis = 1;
  if(digitalRead(rightPin) == HIGH)
    rightAxis++;
  if(digitalRead(leftPin) == HIGH)
    rightAxis--;

  //Envoi des donnes

  //Boutons
  if(prevA != a) {
    Serial.print("A");
    Serial.println(toInt(a));
  }
  if(prevB != b) {
    Serial.print("B");
    Serial.println(toInt(b));  
  }
  if(prevC != c) {
    Serial.print("C");
    Serial.println(toInt(c));
  }
  if(prevJ != j) {
    Serial.print("J");
    Serial.println(toInt(j));
  }  
  
  //Joystick vertical
  if(prevForward != forwardAxis) {
    Serial.print("F");
    Serial.println(forwardAxis);
  }

  //Joystick horizontal
  if(prevRight != rightAxis) {
    Serial.print("R");
    Serial.println(rightAxis);
  }
  
  //Enregistrement des donnees pour le tour suivant
  prevA = a;
  prevB = b;
  prevC = c;
  prevJ = j;
  prevForward = forwardAxis;
  prevRight = rightAxis;

  delay(10);
}

int toInt(bool b) {
  if(b)
    return 1;
  else
    return 0;
}
