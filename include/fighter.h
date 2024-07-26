#ifndef __FIGHTER__
#define __FIGHTER__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define STEP 8
#define GRAVITY 1.8
#define HITPUNCH 50
#define HITKICK 100

typedef struct attack{
    unsigned short punch;
    unsigned short kick;
    unsigned short frame;
    unsigned short totalFrame;
    unsigned short totalKick;
    unsigned short totalCooldown;
    unsigned short cooldown;
    unsigned short hit;
    unsigned char collision;
    //unsigned char life;
    unsigned char actualPicturePunch;
    float xPicturePunch[20];
    ALLEGRO_BITMAP* spritePunch;
    unsigned char actualPictureKick;
    float xPictureKick[26];
    ALLEGRO_BITMAP* spriteKick;
} attack;

attack* fightInit(unsigned char hero);
void fightDestroy(attack* player);

#endif