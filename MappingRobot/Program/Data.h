#ifndef DATA_H
#define DATA_H

#include "Tools/BooleanMatrix.h"
#include "Tools/UCharMatrix.h"
#include "Tools/Vector.h"

// Control algorithm data ------------------------------------------------------

// Intern map
#define MAP_SIZE 72
BooleanMatrix* map = bm_new(MAP_SIZE, MAP_SIZE);

// Low resolution map (Intern map but with a smaller resolution). A pixel in the
// lowResMap is ON if at least 1 pixel of the intern map that touches it is ON
#define LOWRES_SIZE 24
UCharMatrix* lowResMap = newMatrix(LOWRES_SIZE, LOWRES_SIZE)

// Position and rotation (cm and radians)
Vector* position = newVector(0,0);
float rotation = 0;

// Sonar data (last distance measured in cm)
float lastDistance = 0;

// Last forward input (1 = full forward, -1 = full backward)
float forwardInput = 0;
// Last turn input (1 = full right, -1 = full left)
float turnInput = 0;

// True if the path needs to be updated (the map/target just changed)
int needsPathUpdate = 1;

// Settings --------------------------------------------------------------------

//Length of a pixel in cm
float pixelLength = 8;

// Measures --------------------------------------------------------------------

// Forward speed in cm/s
float robotSpeed = 66;

// Turn rate in rad/s
float robotTurnRate = 6;

#endif //DATA_H
