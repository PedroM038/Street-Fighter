#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "joystick.h"

#define RECTANGLE_STEP 15

typedef struct {
    unsigned char base;
    unsigned char height;
    unsigned short x;
    unsigned short y;
    unsigned short squat;
    unsigned short jump;
    joystick* control;
} rectangle;

rectangle* rectangleCreate(unsigned char base, unsigned char height, unsigned short x, unsigned short y, unsigned short maxX, unsigned short maxY);
void rectangleMove(rectangle* element, unsigned char steps, unsigned short trajectory, unsigned short maxX, unsigned short maxY);
void rectangleDestroy(rectangle* element);

#endif
