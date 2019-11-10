
#include "InternMap.h"
#include "Data.h"
#include "Vector.h"
#include "BooleanMatrix.h"
#include "UCharMatrix.h"

#include <math.h>
#include <stdlib.h>

// Turns a pixel ON on the intern map
// Also updates the lowResMap and controlAlgorithm.needsPathUpdate
void turnPixelOn(unsigned int x, unsigned int y) {

    //Stops everything if the pixel is outside the internMap or already ON
    if(!bm_inBounds(internMap, x, y) || bm_get(internMap, x, y))
        return;

    //Sets the pixel to ON
    bm_set(internMap, x, y, 1);

    // The new pixel will set a wall on every pixel on the lowResMap it touches
    for(int j = -1; j <= 1; j++) {
        for(int i = -1; i <= 1; i++) {
            int lrX = (x+i)/3;
            int lrY = (y+j)/3;
            if(inMatrixBounds(lowResMap, lrX, lrY) && (getMatrixValue(lowResMap, lrX, lrY) != 255)) {
                setMatrixValue(lowResMap, lrX, lrY, 255);
                needsPathUpdate = true; //TODO: Seulement si le pixel etait sur le chemin
            }
        }
    }
}

// Checks if a lowResMap pixel should be off (if no real internMap pixel touches it)
int isPixelOff(unsigned int x, unsigned int y) {
    
    x *= 3;
    y *= 3;
    for(int j = -1; j <= 4; j++)
        for(int i = -1; i <= 4; i++)
            if(bm_inBounds(internMap, x+i, y+j) && bm_get(internMap, x+i, y+j))
                return 0;
    return 1;
}

// Turns a pixel OFF on the intern map
// Also updates the lowResMap and controlAlgorithm.needsPathUpdate
void turnPixelOff(unsigned int x, unsigned int y) {

    //Stops everything if the pixel is outside the internMap or already OFF
    if(!bm_inBounds(internMap, x, y) || !bm_get(internMap, x, y))
        return;

    //Sets the pixel to ON
    bm_set(internMap, x, y, 0);

    //Creates an array of offsets for the pixels that can change
    int* toCheck = (int*) malloc(sizeof(int)*8);
    for(int i = 2; i < 8; i++)
        toCheck[i] = -10;
    //Adds the current pixel
    toCheck[0] = 0; toCheck[1] = 0;
    int nbToCheck = 1;

    //Adds the rest
    if(x % 3 == 0) { 
        toCheck[nbToCheck*2] = -1;
        toCheck[nbToCheck*2+1] = 0;
        nbToCheck++;
    }
    if(x % 3 == 2) { 
        toCheck[nbToCheck*2] = 1;
        toCheck[nbToCheck*2+1] = 0;
        nbToCheck++;
    }
    if(y % 3 == 0) { 
        toCheck[nbToCheck*2] = 0;
        toCheck[nbToCheck*2+1] = -1;
        nbToCheck++;
    }
    if(y % 3 == 2) { 
        toCheck[nbToCheck*2] = 0;
        toCheck[nbToCheck*2+1] = 1;
        nbToCheck++;
    }
    if(x % 3 == 0 && y % 3 == 0) { 
        toCheck[nbToCheck*2] = -1;
        toCheck[nbToCheck*2+1] = -1;
        nbToCheck++;
    }
    if(x % 3 == 2 && y % 3 == 2) { 
        toCheck[nbToCheck*2] = 1;
        toCheck[nbToCheck*2+1] = 1;
        nbToCheck++;
    }
    if(x % 3 == 0 && y % 3 == 2) { 
        toCheck[nbToCheck*2] = -1;
        toCheck[nbToCheck*2+1] = 1;
        nbToCheck++;
    }
    if(x % 3 == 2 && y % 3 == 0) { 
        toCheck[nbToCheck*2] = 1;
        toCheck[nbToCheck*2+1] = -1;
        nbToCheck++;
    }
    
    // Checks every pixel (if at least one pixel of the internMap touches the pixel,
    // it will stay black, otherwise it will be freed)
    int i = 0;
    while(toCheck[i] != -10) {

        int lrX = x/3 + toCheck[i];
        int lrY = y/3 + toCheck[i+1];

        // If the pixel is not in the matrix bounds or already off,
        // it will not have to be checked
        if(!inMatrixBounds(lowResMap, lrX, lrY) || (getMatrixValue(lowResMap, lrY, lrX) != 255))
            continue;

        if(isPixelOff(lrX, lrY)) {
            setMatrixValue(lowResMap, lrX, lrY, 254);
            needsPathUpdate = true;
        }

        i += 2;
    }

    free(toCheck);
}

//Updates the internMap according to the position, the rotation
//and the last distance calculated
void internMapUpdate() {

    Vector* wallDir = vectorfromRot(rotation);
    float hitDistance = lastDistance / pixelLength; //In internMap units

    Vector* currentPixel = vectorCopy(position);

    //Empties all the pixels between the robot and the hit point
    for(int i = 0; i < hitDistance; i++) {
        bm_set(internMap, round(currentPixel->x), round(currentPixel->y), 0);
        vectorAdd(currentPixel, wallDir);
    }

    //Fills the pixel at the hit point
    bm_set(internMap, round(currentPixel->x), round(currentPixel->y), 1);
}
