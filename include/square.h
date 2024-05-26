#ifndef __SQUARE__
#define __SQUARE__

#define SQUARE_STEP 20

typedef struct {
    unsigned char side;
    unsigned short x;
    unsigned short y;
} square;

square* squareCreate(unsigned char side, unsigned short x, unsigned short y, unsigned short maxX, unsigned short maxY);
void squareMove(square* element, unsigned char steps, unsigned short trajectory, unsigned short maxX, unsigned short maxY);
void squareDestroy(square* element);

#endif
