#include "../include/fighter.h"

attack* fightInit(){
    attack* p = malloc(sizeof(attack));
    p->frame = 0;
    p->hit = 0;
    p->punch = 0;
    p->kick = 0;
    p->cooldown = 0;
    p->collision = 0;
    p->life = 100;
    return p;
}

void fightDestroy(attack* a){
    free(a);
}