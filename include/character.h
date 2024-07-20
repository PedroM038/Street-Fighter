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
    float xPicture[18];
    unsigned char actualPicture;
    ALLEGRO_BITMAP* sprite;
} stateStop;

typedef struct stateWalking{
    unsigned char isWalking;
    unsigned short frame;
    float xPicture[20];
    unsigned char actualPicture;
    ALLEGRO_BITMAP* sprite;
} stateWalking;

typedef struct stateJump{
    unsigned short isJump;
    unsigned short frame;
    unsigned char isTop;
    double velocityY;
    double accelerationY;
    float xPicture[12];
    unsigned char actualPicture;
    ALLEGRO_BITMAP* sprite;
} stateJump;

typedef struct stateSquat{
    unsigned short isSquat;
    float xPicture[2];
    unsigned char actualPicture;
    ALLEGRO_BITMAP* sprite;
}stateSquat;

typedef struct player{
    unsigned char hero;     //KIRA OR HANZO
    unsigned short base;     //total base measurement
    unsigned short height;   //total height meansurement
    unsigned short xInit;   
    unsigned short yInit;   
    unsigned short x;       //center X point
    unsigned short y;       //center Y point
    //unsigned short squat;   
    unsigned char walkForward;
    unsigned char walkBackward;
    attack* fight;
    joystick* control;
    stateStop* stop;
    stateWalking* walking;
    stateJump* jump;
    stateSquat* squat;
} player;

stateStop* stopInit(unsigned char hero);
stateWalking* walkingInit(unsigned char hero);
stateJump* jumpInit(unsigned char hero);
stateSquat* squatInit(unsigned char hero);

player* playerInit(unsigned char character, unsigned short base, unsigned short height, unsigned short x, 
    unsigned short y, unsigned short maxX, unsigned short maxY);
    
void playerDestroy(player* element);

#endif