#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "joystick.h"

#define RECTANGLE_STEP 10
#define GRAVITY 2

typedef struct {
    unsigned char base;
    unsigned char height;
    unsigned short xInit;
    unsigned short yInit;
    unsigned short x;
    unsigned short y;
    unsigned short squat;
    unsigned short jump;
    unsigned short frame;
    double velocityY;
    double accelerationY;
    joystick* control;
} rectangle;


rectangle* rectangleCreate(unsigned char base, unsigned char height, unsigned short x, unsigned short y, unsigned short maxX, unsigned short maxY);
void rectangleMove(rectangle* element, double steps, unsigned short trajectory, unsigned short maxX, unsigned short maxY);
void rectangleDestroy(rectangle* element);

#endif