class Sonar  {

    parentRobot;
    line;

    hitPoint;
    distance;

    static RANGE = 400;

    constructor(parentRobot) {
        this.parentRobot = parentRobot;
        this.line = new Line(this.parentRobot.position, this.parentRobot.position).setColor("#00FF00");
    }

    update() {

        this.line.setStartEnd(
            this.parentRobot.position,
            Vector.fromOrientation(this.parentRobot.rotation).multiply(Sonar.RANGE).add(this.parentRobot.position)
        );

        //Updates the hitPoint and the distance (closest hit)
        let closest = new Vector(Infinity, Infinity);
        let minDistance = Infinity;
        let lines = sceneHitboxLines.filter(line => this.parentRobot.hitboxLines.indexOf(line) === -1);
        for(let line of lines) {
            let collisionPoint = line.getCollisionPoint(this.line);
            if(collisionPoint != null && Vector.distance(collisionPoint, this.parentRobot.position) < minDistance) {
                minDistance = Vector.distance(collisionPoint, this.parentRobot.position);
                closest = collisionPoint;
            }
        }
        this.hitPoint = closest;
        this.distance = minDistance;
    }

    draw() {
        drawSquare(this.hitPoint, 2, "#FF0000");
    }

    getDistance() {
        return Math.min(this.distance, Sonar.RANGE);
    }
}