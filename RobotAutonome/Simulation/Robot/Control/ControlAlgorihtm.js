class ControlAlgorithm {

    //The length of a pixel of the map in the simulation world units (pixels)
    static PIXEL_LENGTH = 7;
    static INTERNMAP_SIZE = 96; //Must be multiple of 8

    expectedPosition;
    expectedRotation;
    map;
    lowResMap;
    sonar;
    lastUpdateTime = timeSeconds();

    target;

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

        let targetPositions = findPath(this);

        let inputs = this.getMovementInput(targetPositions[0]);
        let forwardInput = inputs[0];
        let turnInput = inputs[1];

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
        //Each pixel of the lowResMap is 4 pixels of the map. If one pixel in each 4x4 square is on, the pixel is on
        for(let y = 0; y < ControlAlgorithm.INTERNMAP_SIZE/4; y++)
            for(let x = 0; x < ControlAlgorithm.INTERNMAP_SIZE/4; x++) {
                let value = ((x, y) => {
                    for(let j = 0; j < 4; j++)
                        for(let i = 0; i < 4; i++)
                            if(this.map.matrix.getValue(i+x*4, j+y*4))
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

    //Calculates the inputs in order to reach the target
    getMovementInput(target) {

        // Calculates the needed turn input to reach the target
        let targetAngle = 180/Math.PI * Math.atan2(target.y - this.expectedPosition.y, target.x - this.expectedPosition.x);
        targetAngle = clampAngle(targetAngle);
        if(targetAngle - this.expectedRotation > 180)
            targetAngle -= 360;
        if(targetAngle - this.expectedRotation < -180)
            targetAngle += 360;
        let angleDiff = Math.abs(targetAngle - this.expectedRotation);
        let turnInput = 0.5 * (targetAngle > this.expectedRotation ? -1 : 1);

        // If no big turn is needed, goes forward
        let forwardInput = angleDiff > 10 ? 0 : 1;

        return [forwardInput, turnInput];
    }
}