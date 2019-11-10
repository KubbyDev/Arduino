#ifndef DATA_H
#define DATA_H

#include "BooleanMatrix.h"
#include "UCharMatrix.h"
#include "Vector.h"

#define MAP_SIZE 72
#define LOWRES_SIZE 24

extern BooleanMatrix* internMap;
extern UCharMatrix* lowResMap;
extern Vector* position;
extern float rotation;
extern float lastDistance;
extern float forwardInput;
extern float turnInput;
extern Vector* target;
extern int needsPathUpdate;
extern unsigned long lastUpdateTime;
extern float pixelLength;
extern float robotSpeed;
extern float robotTurnRate;

#endif //DATA_H
