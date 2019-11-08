#include "InternMap.h"
#include "Data.h"
#include "Tools/Vector.h"
#include "Tools/BooleanMatrix.h"

#include <math.h>

// Turns a pixel ON on the intern map
// Also updates the lowResMap and controlAlgorithm.needsPathUpdate
void turnPixelOn(unsigned int x, unsigned int y) {

    //Stops everything if the pixel is outside the map or already ON
    if(!bm_inBounds(map, x, y) || bm_get(map, x, y))
        return;

    //Sets the pixel to ON
    bm_set(map, x, y, 1);

    // The new pixel will set a wall on every pixel on the lowResMap it touches
    for(int j = -1; j <= 1; j++) {
        for(int i = -1; i <= 1; i++) {
            int lrX = (x+i)/3;
            int lrY = (y+j)/3;
            if(inMatrixBounds(lowResMap, lrX, lrY) && (getMatrixValue(lowResMap, lrX, lrY) !== 255)) {
                setMatrixValue(lowResMap, lrX, lrY, 255);
                needsPathUpdate = true; //TODO: Seulement si le pixel etait sur le chemin
            }
        }
    }
}

// Turns a pixel OFF on the intern map
// Also updates the lowResMap and controlAlgorithm.needsPathUpdate
void turnPixelOff(unsigned int x, unsigned int y) {

    //Stops everything if the pixel is outside the map or already OFF
    if(!bm_inBounds(map, x, y) || !bm_get(map, x, y))
        return;

    //Sets the pixel to ON
    bm_set(map, x, y, 0);




// ONLY WORKS FOR LOWRESMAP_SIZERATION = 3
let toCheck = [[0,0]];
if(x % 3 === 0) toCheck.push([-1, 0]);
if(x % 3 === 2) toCheck.push([1, 0]);
if(y % 3 === 0) toCheck.push([0, -1]);
if(y % 3 === 2) toCheck.push([0, 1]);
if(x % 3 == 0 && y % 3 == 0) toCheck.push([-1, -1]);
if(x % 3 === 2 && y % 3 === 2) toCheck.push([1, 1]);
if(x % 3 === 0 && y % 3 === 2) toCheck.push([-1, 1]);
if(x % 3 === 2 && y % 3 === 0) toCheck.push([1, -1]);

for(let offset of toCheck) {

let lrX = Math.floor(x/ControlAlgorithm.LOWRESMAP_SIZERATIO)+offset[0];
let lrY = Math.floor(y/ControlAlgorithm.LOWRESMAP_SIZERATIO)+offset[1];

if(!inBoundsLowRes(lrX,lrY) || this.controlAlgorithm.lowResMap[lrY*ControlAlgorithm.LOWRESMAP_SIZE + lrX] !== 255)
continue;

if(this.isPixelOff(lrX, lrY)) {
this.controlAlgorithm.lowResMap[lrY*ControlAlgorithm.LOWRESMAP_SIZE + lrX] = 254;
this.controlAlgorithm.needsPathUpdate = true;
}
}
}

isPixelOff(x, y) {
x *= ControlAlgorithm.LOWRESMAP_SIZERATIO;
y *= ControlAlgorithm.LOWRESMAP_SIZERATIO;
for(let j = -1; j <= ControlAlgorithm.LOWRESMAP_SIZERATIO+1; j++)
for(let i = -1; i <= ControlAlgorithm.LOWRESMAP_SIZERATIO+1; i++)
if(inBoundsReal(x+i, y+j) && (this.matrix.getValue(x+i, y+j) === true))
return false;
return true;
}

//Updates the map according to the position, the rotation
//and the last distance calculated
void internMapUpdate() {

    Vector* wallDir = vectorfromRot(rotation);
    float hitDistance = lastDistance / pixelLength; //In map units

    Vector* currentPixel = vectorCopy(position);

    //Empties all the pixels between the robot and the hit point
    for(int i = 0; i < hitDistance; i++) {
        bm_set(map, round(currentPixel->x), round(currentPixel->y), 0);
        vectorAdd(currentPixel, wallDir);
    }

    //Fills the pixel at the hit point
    bm_set(map, round(currentPixel->x), round(currentPixel->y), 1);
}