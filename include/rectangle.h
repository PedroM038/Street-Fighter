#ifndef __RECTANGLE__
#define __RECTANGLE__

#define RECTANGLE_STEP 20

typedef struct {
    unsigned char base;
    unsigned char height;
    unsigned short x;
    unsigned short y;
} rectangle;

rectangle* rectangleCreate(unsigned char base, unsigned char height, unsigned short x, unsigned short y, unsigned short maxX, unsigned short maxY);
void rectangleMove(rectangle* element, unsigned char steps, unsigned short trajectory, unsigned short maxX, unsigned short maxY);
void rectangleDestroy(rectangle* element);

#endif
