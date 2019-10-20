class InternMap {

    matrix;
    controlAlgorithm;

    constructor(controlAlgorithm) {
        this.controlAlgorithm = controlAlgorithm;
        this.matrix = new BooleanMatrix(120, 120);
    }

    update() {

        let wallDirection = Vector.fromOrientation(this.controlAlgorithm.expectedRotation);

        //The *0.24 is for the conversion from simulation world units to intern map units
        let hitDistance = this.controlAlgorithm.sonar.getDistance() / ControlAlgorithm.PIXEL_LENGTH;

        //Empties all the pixels between the robot and the hit point
        for(let i = 0; i < hitDistance; i++) {
            let position = wallDirection.multiply(i).add(this.controlAlgorithm.expectedPosition);
            this.matrix.setValue(Math.round(position.x), Math.round(position.y), false);
        }

        //Fills the pixel at the hit point
        let wallPosition = wallDirection.multiply(hitDistance).add(this.controlAlgorithm.expectedPosition);
        this.matrix.setValue(Math.round(wallPosition.x), Math.round(wallPosition.y), true);
    }

    getClosest() {

        let direction = Vector.fromOrientation(this.controlAlgorithm.expectedRotation);
        let hitDistance = this.controlAlgorithm.sonar.getDistance() / ControlAlgorithm.PIXEL_LENGTH;
        for(let i = -ControlAlgorithm.INACCURACY_THRESHOLD; i <= ControlAlgorithm.INACCURACY_THRESHOLD; i++) {
            let position = direction.multiply(i+hitDistance).add(this.controlAlgorithm.expectedPosition);
            if(this.matrix.getValue(Math.round(position.x), Math.round(position.y)))
                return { found: true, adjust: direction.multiply(i)};
        }

        return { found: false };
    }
}