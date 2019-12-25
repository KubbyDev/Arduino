#include "Data.h"

#include "Navigation.h"

#include "Motors.h"
#include "Sonar.h"

#include "Communication.h"

#include "BooleanMatrix.h"
#include "UCharMatrix.h"
#include "Vector.h"

void setup() {
  
    // Empties the internMap and the low resolution map
    bm_clear(internMap);
    clearMatrix(lowResMap);

    // Initialises the motors and the sonar
    initMotors();
    initSonar();

    // Initialises the communication with the ESP8266
    initCommunication();

    Serial.begin(9600);
    vectorSet(target, 68, 68);
}

void loop() {

    if(Serial.available()) {
        char c = Serial.read();
        if(c == 'c') {
            Serial.println("Cleared");
            bm_clear(internMap);
            for(int i = 0; i < 72*9; i++)
                Serial.print(bm_getByte(internMap, i)); Serial.print(" ");
        }
        if(c == 'f') {
            Serial.println("Target = 68, 68");
            vectorSet(target, 68, 68);
        }
        if(c == 'n') {
            Serial.println("Target = 5, 5");
            vectorSet(target, 5, 5);
        }
    }

    // Updates the communication with the ESP8266
    // (Retrives or sends information to the user if necessary)
    updateCommunication();
    
    // Updates the control algorithm
    // (Changes the values in Data.cpp)
    updateNavigation();
    
    // Updates the speed of the motors
    updateMotors();

    // Lauches a new sonar measurement
    updateSonar();
}
