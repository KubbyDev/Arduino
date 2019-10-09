class Robot extends SceneObject {

    speed = 3;
    turnRate = 2;
    sonarLine = new Line().setColor("#12ff32");

    sonarDistance = 0;
    sonarHitPoint = new Vector(0, 0);

    constructor() {
        super();
        this.controlAlgorithm = new ControlAlgorithm(this);
        this.visibleLines.push(this.sonarLine);
    }

    update() {

        //Asks the control algorithm what to do
        let input = this.controlAlgorithm.update();
        this.moveForward(input[0]);
        this.turn(input[1]);

        //Updates the position of the corners of the robot (and the hitbox at the same time) if necessary
        this.getCorners();

        //Updates the sonar line
        this.sonarLine.setStartEnd(this.position, Vector.fromOrientation(this.rotation).multiply(10000));

        //Updates the sonarHitPoint and the sonarDistance (closest hit)
        let closest = new Vector(Infinity, Infinity);
        let minDistance = Infinity;
        let lines = sceneHitboxLines.filter(line => this.hitboxLines.indexOf(line) === -1);
        for(let line of lines) {
            let collisionPoint = line.getCollisionPoint(this.sonarLine);
            if(collisionPoint != null && Vector.distance(collisionPoint, this.position) < minDistance) {
                minDistance = Vector.distance(collisionPoint, this.position);
                closest = collisionPoint;
            }
        }
        this.sonarHitPoint = closest;
        this.sonarDistance = minDistance;

        //Collisions with walls
        if(this.isColliding()) //This function is in the super class (SceneObject)
            console.log("Collision !");
    }

    draw() {
        super.draw();
        drawSquare(this.sonarHitPoint, 2, "#FF0000");
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