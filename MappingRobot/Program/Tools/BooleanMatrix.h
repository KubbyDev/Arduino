#ifndef BOOLEANMATRIX_H
#define BOOLEANMATRIX_H

typedef struct BooleanMatrix BooleanMatrix;

BooleanMatrix* newMatrix(unsigned int sizeX, unsigned int sizeY);
void destroyMatrix(BooleanMatrix* matrix);

// Getters
int getValue(BooleanMatrix* matrix, unsigned int x, unsigned int y);
unsigned int getSizeX(BooleanMatrix* matrix);
unsigned int getSizeY(BooleanMatrix* matrix);
unsigned char getByte(BooleanMatrix* matrix, unsigned int x, unsigned int y);

//Setters
void setValue(BooleanMatrix* matrix, unsigned int x, unsigned int y, int booleanValue);
void clear(BooleanMatrix* matrix);
void fill(BooleanMatrix* matrix, int booleanValue);

#endif //BOOLEANMATRIX_H
