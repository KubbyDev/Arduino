class Robot extends SceneObject {

    speed = 3;
    turnRate = 2;
    sonarLine = new Line();

    constructor() {
        super();
        this.visibleLines.push(this.sonarLine);
    }

    update() {

        this.turn(0.1);
        this.moveForward(0.3);

        this.sonarLine.setStartEnd(this.position, Vector.fromOrientation(this.rotation).multiply(10000));

        //Collisions avec les murs
        if(this.isColliding())
            console.log("Collision !");
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