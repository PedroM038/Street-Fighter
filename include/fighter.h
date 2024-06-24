#ifndef __FIGHTER__
#define __FIGHTER__

#include <stdio.h>
#include <stdlib.h>

#define STEP 8
#define GRAVITY 2
#define HITPUNCH 10
#define HITKICK 10

typedef struct attack{
    unsigned short punch;
    unsigned short kick;
    unsigned short frame;
    unsigned short cooldown;
    unsigned short hit;
    unsigned char collision;
    unsigned char life;
} attack;

attack* fightInit();
void fightDestroy(attack* player);

#endif