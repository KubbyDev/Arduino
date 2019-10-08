let hitboxLines = [];
let visibleLines = [];
let objects = [];

function updateScene() {
    for(let scobj of objects)
        scobj.update();
}

function drawScene() {
    ctx.clearRect(0,0, canvas.width, canvas.height);
    for(let line of visibleLines)
       line.draw();
    for(let scobj of objects)
        scobj.draw();
}

function addObject(toAdd) {
    objects.push(toAdd);
    toAdd.calcCorners();
    for(let line of toAdd.hitboxLines) hitboxLines.push(line);
    for(let line of toAdd.visibleLines) visibleLines.push(line);
}

function addWall(line) {
    visibleLines.push(line);
    hitboxLines.push(line);
}