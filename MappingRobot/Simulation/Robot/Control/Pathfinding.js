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
    //Each pixel of the lowResMap is 3 pixels of the map. If one pixel in each 3x3 square is on, the pixel is on
    for(let y = 0; y < ControlAlgorithm.LOWRESMAP_SIZE; y++) {
        for(let x = 0; x < ControlAlgorithm.LOWRESMAP_SIZE; x++) {
            controlAlgo.lowResMap[y*ControlAlgorithm.LOWRESMAP_SIZE + x] =
                ((x, y) => {
                    for (let j = 0; j < ControlAlgorithm.LOWRESMAP_SIZERATIO; j++)
                        for (let i = 0; i < ControlAlgorithm.LOWRESMAP_SIZERATIO; i++)
                            if (controlAlgo.map.matrix.getValue(i + x * ControlAlgorithm.LOWRESMAP_SIZERATIO, j + y * ControlAlgorithm.LOWRESMAP_SIZERATIO))
                                return 255;
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
                    if(newX >= 0 && newY >= 0
                        && newX < ControlAlgorithm.LOWRESMAP_SIZE && newY < ControlAlgorithm.LOWRESMAP_SIZE
                        && get(newX, newY)+offset[2] < get(x,y)) {
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
            if(newX >= 0 && newY >= 0
                && newX < ControlAlgorithm.LOWRESMAP_SIZE && newY < ControlAlgorithm.LOWRESMAP_SIZE
                && get(newX, newY) < min) {
                min = get(newX, newY);
                minIndex = i;
            }
        }
        pos = pos.add(new Vector(offsets[minIndex][0], offsets[minIndex][1]));
        res.push(pos.multiply(ControlAlgorithm.LOWRESMAP_SIZERATIO));
        tries++;
    }

    return res;
}