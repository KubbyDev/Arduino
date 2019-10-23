class ControlAlgorithm {

    //The length of a pixel of the map in the simulation world units (pixels)
    static PIXEL_LENGTH = 5;

    expectedPosition;
    expectedRotation;
    map;
    lowResMap;
    sonar;
    lastUpdateTime = timeSeconds();

    targetPosition;

    constructor(sonar) {
        this.sonar = sonar;
        this.map = new InternMap(this);
        this.lowResMap = new InternMap(this);
    }

    resetPositionAndRotation(newPosition, newRotation) {
        this.expectedPosition = newPosition;
        this.expectedRotation = newRotation;
    }

    update() {

        let deltaTime = timeSeconds() - this.lastUpdateTime;
        this.lastUpdateTime = timeSeconds();

        let sonarData = this.sonar.getDistance();

        let forwardInput = 1;
        if(isFinite(sonarData)) //The sonar distance is infinite if the distance > Sonar.RANGE
            forwardInput = sonarData/Sonar.RANGE;

        let targetAngle = 180/Math.PI
            * Math.atan2(this.targetPosition.y - this.expectedPosition.y, this.targetPosition.x - this.expectedPosition.x);
        if(Math.abs(targetAngle - this.expectedRotation) > 180)
            targetAngle *= -1;
        let turnInput = 0.5 * (targetAngle > this.expectedRotation ? -1 : 1);

        //The last factors are the turn rate of the robot and its speed multiplied
        //by the size ratio between the intern map and the simulation world.
        //They will have to be determined experimentaly on the real robot
        this.expectedPosition.x += Math.cos(this.expectedRotation*Math.PI/180)
            * forwardInput * Robot.SPEED/ControlAlgorithm.PIXEL_LENGTH * deltaTime;
        this.expectedPosition.y += Math.sin(this.expectedRotation*Math.PI/180)
            * forwardInput * Robot.SPEED/ControlAlgorithm.PIXEL_LENGTH * deltaTime;
        this.expectedRotation += -turnInput * Robot.TURNRATE * deltaTime;
        this.expectedRotation = clampAngle(this.expectedRotation);

        //Updates the map according to the data of the sonar
        if(isFinite(sonarData)) //The sonar distance is infinite if the distance > Sonar.RANGE
            this.map.update();

        //Calculates the lowResMap for the pathfinding algorithm
        //Each pixel of the lowResMap is 8 pixels of the map. If one pixel in each 8x8 square is on, the pixel is on
        for(let y = 0; y < 15; y++)
            for(let x = 0; x < 15; x++) {
                let value = ((x, y) => {
                    for(let j = 0; j < 8; j++)
                        for(let i = 0; i < 8; i++)
                            if(this.map.matrix.getValue(i+x*8, j+y*8))
                                return 1;
                    return 0;
                })(x, y);
                this.lowResMap.matrix.setValue(x, y, value);
            }

        return [
            forwardInput,
            turnInput,
        ];
    }
}