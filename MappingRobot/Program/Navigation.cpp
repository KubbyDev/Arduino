#include "Navigation.h"
#include "Data.h"
#include "IO/Sonar.h"
#include "Tools/Vector.h"

#include <math.h>

float clampAngle(float* angle) {
    *angle = *angle % (2*PI);
    if(*angle < 0)
        *angle += (2*PI);
}

void getMovementInputs(Vector* target, float* forwardInput, float* turnInput) {

    // Calculates the needed turn input to reach the target
    float targetAngle = atan2(target->y - position->y, 
                              target->x - position->x);
    clampAngle(&targetAngle);
    
    float angleDiff = abs(targetAngle - rotation);

    //If the angle difference is too small, doesn't turn
    if(angleDiff > 2 *PI/180) {

        //Avoids making a turn of more than 180 degrees
        if(targetAngle - rotation > PI) targetAngle -= 2*PI;
        if(targetAngle - rotation < -PI) targetAngle += 2*PI;

        *turnInput = (targetAngle > rotation) ? -1 : 1;
    }
    //If no big turn is needed, can go forward
    else {
        *forwardInput = 1;
    }
}

void navigationUpdate() {

    //Gets the time between this update and the previous one (seconds)
    float deltaTime = 1;              //TODO ! 

    //Sets the value in lastDistance
    sonarUpdate();

    //Pathfinding update
    Vector* targetPosition = newVector(0,0);

    //Calculates the turnInput and the forwardInput to go to targetPosition
    forwardInput = 0;
    turnInput = 0;
    if(targetPosition != NULL)
        getMovementInput(targetPosition, &forwardInput, &turnInput);

    //Updates the position and rotation of the robot on the map
    float speed = forwardInput * robotSpeed/pixelLength * deltaTime;
    position->x += cos(rotation) * speed;
    position->y += sin(rotation) * speed;
    rotation += turnInput * robotTurnRate * deltaTime;
    clampAngle(&rotation);

    //Updates the map according to the data of the sonar
    internMapUpdate();
}