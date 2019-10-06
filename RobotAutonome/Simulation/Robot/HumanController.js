class HumanController {

    getInputs(circuit) {
        return [forwardAxis,rightAxis];
    }
}

const humanController = new HumanController();

forwardAxis = 0;
rightAxis = 0;

document.onkeydown = function(event) {

    switch(event.keyCode) {
        case 38:
            forwardAxis = 1;
            break;
        case 40:
            forwardAxis = -1;
            break;
        case 37:
            rightAxis = 1;
            break;
        case 39:
            rightAxis = -1;
            break;
    }
};
document.onkeyup = function(event){

    switch(event.keyCode) {
        case 38:
            forwardAxis = 0;
            break;
        case 40:
            forwardAxis = 0;
            break;
        case 37:
            rightAxis = 0;
            break;
        case 39:
            rightAxis = 0;
            break;
    }
};



