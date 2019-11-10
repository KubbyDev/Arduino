#include "Data.h"
#include "BooleanMatrix.h"
#include "UCharMatrix.h"
#include "Navigation.h"

void setup() {

    //Empties the internMap and the low resolution map
    bm_clear(internMap);
    clearMatrix(lowResMap);
}

void loop() {

    navigationUpdate();
  
}
