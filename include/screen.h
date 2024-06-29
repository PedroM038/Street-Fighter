#ifndef __SCREEN__
#define __SCREEN__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define XSCREEN 1280
#define YSCREEN 720

typedef struct map{
    ALLEGRO_BITMAP* background;
    unsigned char choiceMap;
} map;

void battleMap(map* m, unsigned char choice);

map* mapInit();

#endif