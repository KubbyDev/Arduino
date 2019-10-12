class Robot extends SceneObject {

    speed = 3;
    turnRate = 2;
    sonar;

    constructor() {
        super();
        this.controlAlgorithm = new ControlAlgorithm(this);
        this.sonar = new Sonar(this);
        this.visibleLines.push(this.sonar.line);
    }

    update() {

        super.update();

        //Updates the sonar
        this.sonar.update();

        //Asks the control algorithm what to do
        let input = this.controlAlgorithm.update();
        this.moveForward(input[0]);
        this.turn(input[1]);

        //Updates the position of the corners of the robot (and the hitbox at the same time) if necessary
        this.getCorners();

        //Collisions with walls
        if(this.isColliding()) //This function is in the super class (SceneObject)
            console.log("Collision !");
    }

    draw() {
        super.draw();
        this.sonar.draw();
    }

    moveForward(enginePower) {
        this.position.x += Math.cos(this.rotation*Math.PI/180)*enginePower*this.speed;
        this.position.y += Math.sin(this.rotation*Math.PI/180)*enginePower*this.speed;
        this.areCornersCorrect = false;
    }

    turn(input) {
        this.rotation += this.turnRate * -input;
        this.areCornersCorrect = false;
    }
}