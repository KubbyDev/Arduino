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
}

void loop() {

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
