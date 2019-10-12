class ControlAlgorithm {

    parentRobot; //The robot controled by this class

    expectedPosition;
    expectedRotation;
    map;

    constructor(parentRobot) {
        this.parentRobot = parentRobot;
        this.map = new InternMap();
    }

    resetPositionAndRotation(newPosition, newRotation) {
        this.expectedPosition = newPosition;
        this.expectedRotation = newRotation;
    }

    update() {

        let sonarData = this.parentRobot.sonar.getDistance();
        let forwardInput = 0.3 * sonarData/Sonar.RANGE;
        let turnInput = 0.1;

        //The last factors are the turn rate of the robot and its speed multiplied
        //by the size ratio between the intern map and the simulation world.
        //They will have to be determined experimentaly on the real robot
        this.expectedPosition.x += Math.cos(this.expectedRotation*Math.PI/180) * forwardInput * 3*0.24;
        this.expectedPosition.y += Math.sin(this.expectedRotation*Math.PI/180) * forwardInput * 3*0.24;
        this.expectedRotation += -turnInput * 2;

        //Updates the map according to the data of the sonar
        if(isFinite(sonarData)) //The sonar distance is infinite if the distance > Sonar.RANGE
            this.map.update(this.expectedPosition, this.expectedRotation, sonarData * 0.24);
        this.map.draw(this.expectedPosition, this.expectedRotation);

        return [
            forwardInput,
            turnInput,
        ];
    }
}