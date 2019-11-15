#include "Data.h"

#include "Navigation.h"

#include "Motors.h"
#include "Sonar.h"

#include "BooleanMatrix.h"
#include "UCharMatrix.h"
#include "Vector.h"

/* DEBUG 
#include "MemoryFree.h"
*/

void setup() {
  
    // Empties the internMap and the low resolution map
    bm_clear(internMap);
    clearMatrix(lowResMap);

    // Initialises the motors and the sonar
    initMotors();
    initSonar();

    vectorSet(target, 68, 68);

    /* DEBUG
    navigationUpdate();
    updateMotors();
    updateSonar();
    Serial.begin(9600);
    for(int y = 0; y < LOWRES_SIZE; y++) {
      for(int x = 0; x < LOWRES_SIZE; x++) {
        Serial.print(getMatrixValue(lowResMap, x, y));
        Serial.print(" ");
      }
      Serial.println();
    }
    */
}

void loop() {

    /* DEBUG 
    Serial.println("-----------------------------------");
    Serial.print("PosX: ");Serial.print(position->x);Serial.println();
    Serial.print("PosY: ");Serial.print(position->y);Serial.println();
    Serial.print("Rot: ");Serial.print(rotation);Serial.println();
    Serial.print("ForI: ");Serial.print(forwardInput);Serial.println();
    Serial.print("TurI: ");Serial.print(turnInput);Serial.println();
    Serial.print("Free Memory ");Serial.print(freeMemory());Serial.println();
    */
    
    // Updates the control algorithm
    navigationUpdate();
    
    // Updates the speed of the motors
    updateMotors();

    // Lauches a new sonar measure
    updateSonar();
}
