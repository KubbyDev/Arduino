class ControlAlgorithm {

    parentRobot; //The robot controled by this class
    static SONAR_TRUST_THRESHOLD = 400;

    constructor(parentRobot) {
        this.parentRobot = parentRobot;
    }

    update() {
        return [
            0.3 * this.parentRobot.sonarDistance/ControlAlgorithm.SONAR_TRUST_THRESHOLD,
            0.1
        ];
    }
}