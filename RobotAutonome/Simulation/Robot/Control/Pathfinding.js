function findPath(controlAlgo) {

    // This algorithm is aweful I'm ashamed
    // BUT ! It uses only n integers, n being the number of pixels of the lowresmap. So it fits my usage

    function get(x, y) {
        return controlAlgo.lowResMap[y*ControlAlgorithm.INTERNMAP_SIZE/4 + x];
    }

    function set(x, y, val) {
        controlAlgo.lowResMap[y*ControlAlgorithm.INTERNMAP_SIZE/4 + x] = val;
    }

    //Calculates the lowResMap
    //Each pixel of the lowResMap is 4 pixels of the map. If one pixel in each 4x4 square is on, the pixel is on
    for(let y = 0; y < ControlAlgorithm.INTERNMAP_SIZE/4; y++) {
        for(let x = 0; x < ControlAlgorithm.INTERNMAP_SIZE/4; x++) {
            controlAlgo.lowResMap[y*ControlAlgorithm.INTERNMAP_SIZE/4 + x] =
                ((x, y) => {
                    for (let j = 0; j < 4; j++)
                        for (let i = 0; i < 4; i++)
                            if (controlAlgo.map.matrix.getValue(i + x * 4, j + y * 4))
                                return 255;
                    return 254;
                })(x, y);
        }
    }

    set(Math.round(controlAlgo.target.x/4), Math.round(controlAlgo.target.y/4), 0);

    let changed = true;
    while(changed) {

        changed = false;
        for(let y = 0; y < ControlAlgorithm.INTERNMAP_SIZE/4; y++) {
            for(let x = 0; x < ControlAlgorithm.INTERNMAP_SIZE/4; x++) {
                if(get(x, y) === 255)
                    continue;
                if(x > 0 && get(x-1, y)+1 < get(x, y)) {
                    set(x, y, get(x-1, y)+1);
                    changed = true;
                }
                if(y > 0 && get(x, y-1)+1 < get(x, y)) {
                    set(x, y, get(x, y-1)+1);
                    changed = true;
                }
                if(x < ControlAlgorithm.INTERNMAP_SIZE/4 -1 && get(x+1, y)+1 < get(x, y)) {
                    set(x, y, get(x+1, y)+1);
                    changed = true;
                }
                if(y < ControlAlgorithm.INTERNMAP_SIZE/4 -1 && get(x, y+1)+1 < get(x, y)) {
                    set(x, y, get(x, y+1)+1);
                    changed = true;
                }
            }
        }
    }

    //Reconstructs the path
    let pos = controlAlgo.expectedPosition.divide(4).round();
    let nbSteps = get(pos.x, pos.y);
    let res = [];
    for(let i = nbSteps-1; i >= 0; i--) {
        if(pos.x > 0 && get(pos.x-1, pos.y) === i)
            pos = new Vector(pos.x-1, pos.y);
        else if(pos.y > 0 && get(pos.x, pos.y-1) === i)
            pos = new Vector(pos.x, pos.y-1);
        else if(pos.x < ControlAlgorithm.INTERNMAP_SIZE/4 -1 && get(pos.x+1, pos.y) === i)
            pos = new Vector(pos.x+1, pos.y);
        else if(pos.y < ControlAlgorithm.INTERNMAP_SIZE/4 -1 && get(pos.x, pos.y+1) === i)
            pos = new Vector(pos.x, pos.y+1);
        res.push(pos.multiply(4));
    }

    return res;
}