#ifndef __CHARACTER__
#define __CHARACTER__

#include <stdio.h>
#include <stdlib.h>

#include "fighter.h"
#include "joystick.h"

#define KIRA 1
#define HANZO 2

typedef struct player{
    unsigned char hero;     //KIRA OR HANZO
    unsigned char base;     //total base measurement
    unsigned char height;   //total height meansurement
    unsigned short xInit;   
    unsigned short yInit;   
    unsigned short x;       //center X point
    unsigned short y;       //center Y point
    unsigned short squat;   
    unsigned short jump;
    unsigned char walkForward;
    unsigned char walkBackward;
    double velocityY;
    double accelerationY;
    attack* fight;
    joystick* control;
} player;

player* playerInit();
void playerDestroy(player* element);

#endif