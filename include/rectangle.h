#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "joystick.h"

#define RECTANGLE_STEP 10
#define GRAVITY 2

typedef struct fight{
    unsigned short punch;
    unsigned short frame;
    unsigned short punchCooldown;
    unsigned short hit;
    unsigned char walkForward;
    unsigned char walkBackward;
    unsigned char collision;
} fight;

typedef struct rectangle{
    unsigned char base;
    unsigned char height;
    unsigned short xInit;
    unsigned short yInit;
    unsigned short x;
    unsigned short y;
    unsigned short squat;
    unsigned short jump;
    double velocityY;
    double accelerationY;
    fight* attackPunch;
    joystick* control;
} rectangle;


rectangle* rectangleCreate(unsigned char base, unsigned char height, unsigned short x, unsigned short y, unsigned short maxX, unsigned short maxY);
void rectangleMove(rectangle* element, double steps, unsigned short trajectory, unsigned short maxX, unsigned short maxY);
void rectangleDestroy(rectangle* element);


//fighter.h
fight* punchInit();
unsigned char punchCollision(rectangle* attacker, rectangle* target);
void updatePunch(rectangle* attacker, rectangle* target);
void fightDestroy(rectangle* player);

#endif
