//Draws a 4 points polygon defined by the points in the points array
function drawRect(points, color) {
    ctx.fillStyle = color;
    ctx.beginPath();
    ctx.moveTo(points[0].x, points[0].y);
    ctx.lineTo(points[1].x, points[1].y);
    ctx.lineTo(points[2].x, points[2].y);
    ctx.lineTo(points[3].x, points[3].y);
    ctx.closePath();
    ctx.fill();
}

//Draws a square with given position (center), halfside (size length / 2), and color
function drawSquare(position, halfside, color) {
    ctx.fillStyle = color;
    ctx.rect(position.x - halfside, position.y - halfside, halfside*2, halfside*2);
    ctx.fill();
}
