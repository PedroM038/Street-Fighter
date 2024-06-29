#include "../include/character.h"
#include <allegro5/allegro_image.h>

player* playerInit(unsigned char character, unsigned short base, unsigned short height, unsigned short x, 
    unsigned short y, unsigned short maxX, unsigned short maxY){
    
    if ((x - base/2 < 0) || (x + base/2 > maxX) || (y - height/2 < 0) || (y + height/2 > maxY)) return NULL;

    player *newPlayer = (player*) malloc(sizeof(player));
    newPlayer->hero = character;
    newPlayer->base = base;
    newPlayer->height = height;
    newPlayer->xInit = x;
    newPlayer->yInit = y;
    newPlayer->x = x;
    newPlayer->y = y;
    newPlayer->squat = 0;
    newPlayer->jump = 0;
    newPlayer->isTop = 0;
    newPlayer->velocityY = 0;
    newPlayer->accelerationY = GRAVITY;
    newPlayer->control = joystickCreate();
    newPlayer->fight = fightInit();
    newPlayer->stop = stopInit();
    return newPlayer;
}

stateStop* stopInit(){
    stateStop* a = malloc(sizeof(stateStop));
    a->frame = 0;
    a->isStop = 1;
}

void playerDestroy(player* element){
    
    al_destroy_bitmap(element->stop->picture);
    free(element->stop);
    joystickDestroy(element->control);
    fightDestroy(element->fight);
    free(element);
}