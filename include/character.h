#ifndef __CHARACTER__
#define __CHARACTER__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>

#include "fighter.h"
#include "joystick.h"

#define KIRA 1
#define HANZO 2

typedef struct stateStop{
    unsigned char isStop;
    unsigned short frame;
    ALLEGRO_BITMAP* picture;    
} stateStop;

typedef struct stateWalking{
    unsigned char isWalking;
    unsigned short frame;
    ALLEGRO_BITMAP* picture;
    ALLEGRO_BITMAP* walkForwardFrames[12];
    ALLEGRO_BITMAP* walkBackwardFrames[12];
} stateWalking;

typedef struct player{
    unsigned char hero;     //KIRA OR HANZO
    unsigned short base;     //total base measurement
    unsigned short height;   //total height meansurement
    unsigned short xInit;   
    unsigned short yInit;   
    unsigned short x;       //center X point
    unsigned short y;       //center Y point
    unsigned short squat;   
    unsigned short jump;
    unsigned char walkForward;
    unsigned char walkBackward;
    unsigned char isTop;
    double velocityY;
    double accelerationY;
    attack* fight;
    joystick* control;
    stateStop* stop;
    stateWalking* walking;
} player;

stateStop* stopInit();
stateWalking* walkingInit();

player* playerInit(unsigned char character, unsigned short base, unsigned short height, unsigned short x, 
    unsigned short y, unsigned short maxX, unsigned short maxY);
    
void playerDestroy(player* element);

#endif