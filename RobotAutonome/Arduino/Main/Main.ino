#include "BooleanMatrix.h"

int pin = 2;

BooleanMatrix* matrix;

void setup() {

  Serial.begin(9600);
}

void loop() {
  
  BooleanMatrix* matrix = newMatrix(8, 8);
  fill(matrix, 1);

  setValue(matrix, 1, 1, 0);

  for(unsigned int y = 0; y < getSizeY(matrix); y++) {
    for(unsigned int x = 0; x < getSizeX(matrix); x++)
      Serial.write((getValue(matrix, x, y) + '0'));
    Serial.write("\n");
  }

  delay(5000);
}
