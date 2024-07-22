#ifndef __HEALTH__
#define __HEALTH__

#include "fighter.h"
#include "screen.h"

#define LIFE 500
#define GREEN 0
#define YELLOW 1
#define RED 2

typedef struct healthPlayer{
    unsigned short life;
    ALLEGRO_COLOR color;
    ALLEGRO_BITMAP* picturePlayer;
    unsigned short xEnd;
    unsigned short yEnd;
    unsigned short yInit;
    unsigned short xInit; 
} healthPlayer;

healthPlayer* healthInit(unsigned char hero, unsigned char player);
void healthDestroy(healthPlayer* h);

#endif