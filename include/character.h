#ifndef __CHARACTER__
#define __CHARACTER__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>

#include "fighter.h"
#include "joystick.h"
#include "health.h"

#define KIRA 1
#define HANZO 2
#define AIKO 3
#define YUNA 4

typedef struct stateDead{
    unsigned char flag;
    unsigned short cooldown;
    unsigned char isDead;
    unsigned short frame;
    float xPicture[20];
    unsigned char actualPicture;
    ALLEGRO_BITMAP* sprite;
} stateDead;

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
    unsigned char walkForward;
    unsigned char walkBackward;
    unsigned char wins;
    unsigned short cooldown;
    staminaPlayer* staminaStatus;
    healthPlayer* healthStatus;
    attack* fight;
    joystick* control;
    stateStop* stop;
    stateWalking* walking;
    stateJump* jump;
    stateSquat* squat;
    stateDead* dead;
    special* specialAttack;
} player;

special* specialInit(unsigned char hero);
stateDead* deadInit(unsigned char hero);
stateStop* stopInit(unsigned char hero);
stateWalking* walkingInit(unsigned char hero);
stateJump* jumpInit(unsigned char hero);
stateSquat* squatInit(unsigned char hero);
staminaPlayer* staminaCreate(unsigned char player);

player* playerInit(unsigned char character, unsigned short base, unsigned short height, unsigned short x, 
    unsigned short y, unsigned short maxX, unsigned short maxY, unsigned char p);
    
void reInitp1 (player* p1);
void reInitp2 (player* p2);
void playerDestroy(player* element);

#endif