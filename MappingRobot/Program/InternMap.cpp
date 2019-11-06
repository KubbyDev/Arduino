#include "InternMap.h"
#include "Data.h"
#include "Tools/Vector.h"
#include "Tools/BooleanMatrix.h"

#include <math.h>

//Updates the map according to the position, the rotation
//and the last distance calculated
void internMapUpdate() {

    Vector* wallDir = vectorfromRot(rotation);
    float hitDistance = lastDistance / pixelLength; //In map units
 
    Vector* currentPixel = vectorCopy(position);

    //Empties all the pixels between the robot and the hit point
    for(int i = 0; i < hitDistance; i++) {
        setValue(map, round(currentPixel->x), round(currentPixel->y), 0);
        vectorAdd(currentPixel, wallDir);
    }

    //Fills the pixel at the hit point
    setValue(map, round(currentPixel->x), round(currentPixel->y), 1);
}
