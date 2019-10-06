class Car {

    controller;      //Le code qui prend les decision de controle de la voiture (le conducteur)

    position = new Vector(0,0);
    rotation = 0;
    width = 5;
    length = 12;
    color = '#' + (Math.random().toString(16) + "000000").substring(2,8);
    speed = 3;
    turnRate = 2;

    alive = true;
    nextCheckpoint = 0;  //Identifiant du prochain checkpoint a passer

    corners = [new Vector(0,0), new Vector(0,0), new Vector(0,0), new Vector(0,0)];  //Stocke la position des 4 coins de la voiture
    areCornersCorrect = false; //Passe a true apres le calcul des coins, et a false apres mouvement de la voiture
    hitbox = [new Line(), new Line(), new Line(), new Line()]; //Stocke la position de la hitbox (calculee en meme temps que les coins)

    constructor(isHuman = false) {

        if(isHuman)
            this.controller = humanController;
        else
            this.controller = new NetworkController(this);
    }

    /***
     * Recupere les ordres venant du controller et les applique
     * Calcule les collisions (checkpoints compris) et bouge la voiture
     * @param circuit
     */
    update(circuit) {

        let inputs = this.controller.getInputs(circuit.lines);

        this.moveForward(inputs[0]);
        this.turn(inputs[1]);

        //Collisions avec les murs
        if(this.isColliding(circuit.lines))
            this.alive = false;

        //Collisions avec le prochain checkpoint
        if(this.nextCheckpoint < circuit.checkpoints.length && this.isColliding([circuit.checkpoints[this.nextCheckpoint].line]))
            this.nextCheckpoint++;
    }

    setColor(color) {
        this.color = color;
        return this;
    }

    setPosition(x, y) {
        this.position = new Vector(x,y);
        return this;
    }

    setRotation(r) {
        this.rotation = r;
        return this;
    }

    /***
     * Renvoie les coins de la voiture (si ils sont deja calcules, ne les recalcule pas)
     * La hitbox n'est pas renvoiee, mais elle est calculee aussi
     * @returns {*[]}
     */
    getCorners() {

        if(!this.areCornersCorrect)
            this.calcCorners();

        return this.corners;
    }

    /***
     * Calcule la position des coins et de la hitbox de la voiture
     */
    calcCorners() {

        let degR = this.rotation*Math.PI/180;

        this.corners[0] = new Vector(
            this.position.x + this.length*Math.cos(degR) - this.width*Math.sin(degR),
            this.position.y + this.length*Math.sin(degR) + this.width*Math.cos(degR)
        );

        this.corners[1] = new Vector(
            this.position.x + this.length*Math.cos(degR) + this.width*Math.sin(degR),
            this.position.y + this.length*Math.sin(degR) - this.width*Math.cos(degR)
        );

        this.corners[2] = new Vector(
            this.position.x - this.length*Math.cos(degR) + this.width*Math.sin(degR),
            this.position.y - this.length*Math.sin(degR) - this.width*Math.cos(degR)
        );

        this.corners[3] = new Vector(
            this.position.x - this.length*Math.cos(degR) - this.width*Math.sin(degR),
            this.position.y - this.length*Math.sin(degR) + this.width*Math.cos(degR)
        );

        this.hitbox[0].setStartEnd(this.corners[0], this.corners[1]);
        this.hitbox[1].setStartEnd(this.corners[1], this.corners[2]);
        this.hitbox[2].setStartEnd(this.corners[2], this.corners[3]);
        this.hitbox[3].setStartEnd(this.corners[3], this.corners[0]);

        this.areCornersCorrect = true;
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

    /***
     * Regarde si la voiture est en collision avec la liste de lignes en parametre
     * @param lines
     * @returns {boolean}
     */
    isColliding(lines) {

        this.getCorners();

        for(let line of this.hitbox)
            if(line.isColliding(lines))
                return true;

        return false;
    }

    draw() {

        drawRect(this.getCorners(), this.color);

        /*
        for(let line of this.hitbox)
            line.draw();
         */
    }
}