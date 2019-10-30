#ifndef DATA_H
#define DATA_H

#include "Tools/BooleanMatrix.h"
#include "Tools/Vector.h"

// Control algorithm data -----------------------------------------------------

// Intern map
#define MAP_SIZE 96
BooleanMatrix* map = newMatrix(MAP_SIZE, MAP_SIZE);

// Position and rotation (cm and radians)
Vector* position = newVector(0,0);
float rotation = 0;

// Sonar data (last distance measured in cm)
float lastDistance

// Last forward input (1 = full forward, -1 = full backward)
float forwardInput = 0;
// Last turn input (1 = full right, -1 = full left)
float turnInput = 0;

// Settings -------------------------------------------------------------------

//Length of a pixel in cm
float pixelLength = 8;

// Measures -------------------------------------------------------------------

// Forward speed in cm/s
float robotSpeed = 66;

// Turn rate in rad/s
float robotTurnRate = 6;

#endif //DATA_H