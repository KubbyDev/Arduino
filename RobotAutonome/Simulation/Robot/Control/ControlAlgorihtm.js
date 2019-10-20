class ControlAlgorithm {

    //If the sonar finds a wall and the distance between the closest point on the map and the found point is
    //less than this threshold, the robot will reposition itself instead of making a new point. In intern map units
    static INACCURACY_THRESHOLD = 3; //Must be an integer
    //The length of a pixel of the map in the simulation world units (pixels)
    static PIXEL_LENGTH = 5;

    expectedPosition;
    expectedRotation;
    map;
    lowResMap;
    sonar;

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

        let sonarData = this.sonar.getDistance();
        let forwardInput = 0.3 * sonarData/Sonar.RANGE;
        let turnInput = 0.1;

        //The last factors are the turn rate of the robot and its speed multiplied
        //by the size ratio between the intern map and the simulation world.
        //They will have to be determined experimentaly on the real robot
        this.expectedPosition.x += Math.cos(this.expectedRotation*Math.PI/180) * forwardInput * 3/ControlAlgorithm.PIXEL_LENGTH;
        this.expectedPosition.y += Math.sin(this.expectedRotation*Math.PI/180) * forwardInput * 3/ControlAlgorithm.PIXEL_LENGTH;
        this.expectedRotation += -turnInput * 2;

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