function findPath(controlAlgo) {

    // This algorithm is awful I'm ashamed
    // BUT ! It uses only n integers, n being the number of pixels of the lowresmap. So it fits my usage

    function get(x, y) {
        return controlAlgo.lowResMap[y*ControlAlgorithm.LOWRESMAP_SIZE + x];
    }

    function set(x, y, val) {
        controlAlgo.lowResMap[y*ControlAlgorithm.LOWRESMAP_SIZE + x] = val;
    }

    //Calculates the lowResMap
    //Each pixel on the lowResMap represents a 3x3 square in the real map.
    //It is lit if at least one pixel in a 5x5 square in the real map is lit.
    for(let y = 0; y < ControlAlgorithm.LOWRESMAP_SIZE; y++) {
        for(let x = 0; x < ControlAlgorithm.LOWRESMAP_SIZE; x++) {
            controlAlgo.lowResMap[y*ControlAlgorithm.LOWRESMAP_SIZE + x] =
                ((x, y) => {
                    let add = Math.floor(ControlAlgorithm.LOWRESMAP_SIZERATIO/2);
                    for (let j = -add; j <= ControlAlgorithm.LOWRESMAP_SIZERATIO+add; j++) {
                        for (let i = -add; i < ControlAlgorithm.LOWRESMAP_SIZERATIO+add; i++) {
                            let testX = i + x * ControlAlgorithm.LOWRESMAP_SIZERATIO;
                            let testY = j + y * ControlAlgorithm.LOWRESMAP_SIZERATIO;
                            if (inBoundsReal(testX, testY) && controlAlgo.map.matrix.getValue(testX, testY))
                                return 255;
                        }
                    }
                    return 254;
                })(x, y);
        }
    }

    const target = controlAlgo.target.divide(ControlAlgorithm.LOWRESMAP_SIZERATIO).round();
    set(target.x, target.y, 0);

    //List of all possible movements with their associated cost
    const offsets = [
        [1,0,1], [1,1,1.414], [0,1,1], [-1,1,1.414], [-1,0,1], [-1,-1,1.414], [0,-1,1], [1,-1,1.414]
    ];

    //Calculates the distances from the target
    let changed = true;
    while(changed) {

        changed = false;
        for(let y = 0; y < ControlAlgorithm.LOWRESMAP_SIZE; y++) {
            for(let x = 0; x < ControlAlgorithm.LOWRESMAP_SIZE; x++) {
                if(get(x, y) === 255)
                    continue;
                for(let offset of offsets) {
                    let newX = x+offset[0];
                    let newY = y+offset[1];
                    if(inBoundsLowRes(newX, newY) && get(newX, newY)+offset[2] < get(x,y)) {
                        set(x, y, get(newX, newY)+offset[2]);
                        changed = true;
                    }
                }
            }
        }
    }

    //Reconstructs the path
    let pos = controlAlgo.expectedPosition.divide(ControlAlgorithm.LOWRESMAP_SIZERATIO).round();
    let res = [];
    let tries = 0;
    while(!pos.equals(target, 0.5) && tries < ControlAlgorithm.LOWRESMAP_SIZE*ControlAlgorithm.LOWRESMAP_SIZE) {
        let minIndex = 0;
        let min = Infinity;
        for(let i = 0; i < offsets.length; i++) {
            let newX = pos.x+offsets[i][0];
            let newY = pos.y+offsets[i][1];
            if(inBoundsLowRes(newX, newY) && get(newX, newY) < min) {
                min = get(newX, newY);
                minIndex = i;
            }
        }
        pos = pos.add(new Vector(offsets[minIndex][0], offsets[minIndex][1]));
        res.push(pos.multiply(ControlAlgorithm.LOWRESMAP_SIZERATIO));
        tries++;
    }

    //Removes all the useless keys on the path
    let current = controlAlgo.expectedPosition.divide(ControlAlgorithm.LOWRESMAP_SIZERATIO).round();
    let cleaned = [];
    let i = 0; //i is the point that will possibly be removed
    while(i < res.length-1) {
        if(!areAligned(current, res[i], res[i+1])) {
            cleaned.push(res[i]);
            current = res[i];
        }
        i++;
    }
    if(res.length > 0)
        cleaned.push(res[res.length-1]); //The target is always in the path

    return cleaned;
}

function areAligned(start, middle, end) {
    let u = middle.subtract(start);
    let v = end.subtract(start);
    if(v.x === 0) return u.x === 0;
    if(v.y === 0) return u.y === 0;
    return Math.abs(u.x/v.x - u.y/v.y) < 0.01;
}

function inBoundsLowRes(x, y) {
    return x >= 0 && y >= 0
    && x < ControlAlgorithm.LOWRESMAP_SIZE && y < ControlAlgorithm.LOWRESMAP_SIZE;
}

function inBoundsReal(x, y) {
    return x >= 0 && y >= 0
        && x < ControlAlgorithm.INTERNMAP_SIZE && y < ControlAlgorithm.INTERNMAP_SIZE;
}