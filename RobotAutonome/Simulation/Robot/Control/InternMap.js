class InternMap {

    matrix;

    constructor() {
        this.matrix = new BooleanMatrix(120, 120);
    }

    update(expectedPosition, expectedRotation, distance) {
        let wallPosition = Vector.fromOrientation(expectedRotation).multiply(distance).add(expectedPosition);
        this.matrix.setValue(Math.round(wallPosition.x), Math.round(wallPosition.y), true);
    }

    draw(robotPosition, robotRotation) {

        let offsetX = 550;
        let offsetY = 10;

        //Clears the map with grey so we can see the bounds
        ctx.fillStyle = "#CCCCCC";
        ctx.fillRect(offsetX, offsetY, 120*4, 120*4);

        //Sets every pixel where there is something to black
        ctx.fillStyle = "#000000";
        for (let y = 0; y < this.matrix.sizeY; y++)
            for (let x = 0; x < this.matrix.sizeX; x++)
                if (this.matrix.getValue(x, y))
                    ctx.fillRect(offsetX + (x*4), offsetY + (y*4), 4, 4);

        //Draw the robot
        ctx.fillStyle = "#ff0938";
        ctx.fillRect(offsetX + (robotPosition.x)*4 +2 -5, offsetY + (robotPosition.y)*4 +2 -5, 10, 10);
    }
}