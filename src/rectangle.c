#include <stdio.h>
#include <stdlib.h>
#include "../include/rectangle.h"

rectangle* rectangleCreate(unsigned char base, unsigned char height, unsigned short x, unsigned short y, unsigned short maxX, unsigned short maxY){
    if ((x - base/2 < 0) || (x + base/2 > maxX) || (y - height/2 < 0) || (y + height/2 > maxY)) return NULL;

    rectangle *newRectangle = (rectangle*) malloc(sizeof(rectangle));
    newRectangle->base = base;
    newRectangle->height = height;
    newRectangle->xInit = x;
    newRectangle->yInit = y;
    newRectangle->x = x;
    newRectangle->y = y;
    newRectangle->squat = 0;
    newRectangle->jump = 0;
    newRectangle->velocityY = 0;
    newRectangle->accelerationY = GRAVITY;
    newRectangle->control = joystickCreate();
    newRectangle->fight = fightInit();
    return newRectangle;
}

void rectangleMove(rectangle* element, double steps, unsigned short trajectory, unsigned short maxX, unsigned short maxY){

    if (!trajectory){ //esquerda
        if ((element->x - steps*RECTANGLE_STEP) - element->base/2 >= 0)
            element->x = element->x - steps*RECTANGLE_STEP;
    }

    else if (trajectory == 1){ //direita
        if ((element->x + steps*RECTANGLE_STEP) + element->base/2 <= maxX) 
            element->x = element->x + steps*RECTANGLE_STEP;
    }

    else if (trajectory == 2){ //cima
        if ((element->y - steps*RECTANGLE_STEP) - element->height/2 >= 0) 
            element->y = element->y - steps*RECTANGLE_STEP;
    }

    else if (trajectory == 3){ //baixo
        if ((element->y + steps*RECTANGLE_STEP) + element->height/2 <= maxY) 
            element->y = element->y + steps*RECTANGLE_STEP;
    }
}

void rectangleDestroy(rectangle* element){
    joystickDestroy(element->control);
    fightDestroy(element);
    free(element);
}

attack* fightInit(){
    attack* p = malloc(sizeof(attack));
    p->frame = 0;
    p->hit = 0;
    p->punch = 0;
    p->kick = 0;
    p->cooldown = 0;
    p->walkBackward = 0;
    p->walkForward = 0;
    p->collision = 0;
    p->life = 100;
    return p;
}

void updatePunch(rectangle* attacker, rectangle* target) {
    if (attacker->fight->punch) {
        // Verifica a colisão do soco
        if (punchCollision(attacker, target)) {
            attacker->fight->collision = 1;
            attacker->fight->life -= HITPUNCH;
        }

        // Atualiza o frame do soco
        attacker->fight->frame++;
        if (attacker->fight->frame > 10) {
            attacker->fight->punch = 0;
            attacker->fight->frame = 0;
            attacker->fight->hit = 0;
            attacker->fight->collision = 0;
            attacker->fight->cooldown = 30;
        }
    } else if (attacker->fight->cooldown > 0) {
        attacker->fight->cooldown --;
    }
}

unsigned char punchCollision(rectangle* attacker, rectangle* target) {
    
    // Ajuste os valores conforme necessário para o alcance do soco
    unsigned short punchReach = (attacker->base / 2) + 70;

    if (attacker->x <= target->x){
        attacker->fight->walkForward = 1;
        attacker->fight->walkBackward = 0; 
    }
    else{
        attacker->fight->walkBackward = 1;
        attacker->fight->walkForward = 0;
    }

    if (attacker->fight->punch) {
        if (attacker->fight->walkForward &&
            attacker->x + punchReach >= target->x - target->base / 2 &&
            attacker->x <= target->x + target->base / 2 &&
            attacker->y + attacker->height / 2 >= target->y - target->height / 2 &&
            attacker->y - attacker->height / 2 <= target->y + target->height / 2 &&
            attacker->fight->hit == 0) {
            attacker->fight->hit = 1;
            return 1;
        }

        if (attacker->fight->walkBackward &&
            attacker->x - punchReach <= target->x + target->base / 2 &&
            attacker->x >= target->x - target->base / 2 &&
            attacker->y + attacker->height / 2 >= target->y - target->height / 2 &&
            attacker->y - attacker->height / 2 <= target->y + target->height / 2 &&
            attacker->fight->hit == 0) {
            attacker->fight->hit = 1;
            return 1;
        }
    }
    return 0;
}

unsigned char kickCollision(rectangle* attacker, rectangle* target){
    
    // Ajuste os valores conforme necessário para o alcance do soco
    unsigned short kickReach = (attacker->base / 2) + 70;

    if (attacker->x <= target->x){
        attacker->fight->walkForward = 1;
        attacker->fight->walkBackward = 0; 
    }
    else{
        attacker->fight->walkBackward = 1;
        attacker->fight->walkForward = 0;
    }

    if (attacker->fight->kick) {
        if (attacker->fight->walkForward && 
            attacker->x + kickReach >= target->x - target->base / 2 &&
            attacker->x <= target->x + target->base / 2 &&
            attacker->y + attacker->height / 2 >= target->y - target->height / 2 &&
            attacker->y - attacker->height / 2 <= target->y + target->height / 2 &&
            attacker->fight->hit == 0) {
            attacker->fight->hit = 1;
            return 1;
        }

        if (attacker->fight->walkBackward &&
            attacker->x - kickReach <= target->x + target->base / 2 &&
            attacker->x >= target->x - target->base / 2 &&
            attacker->y + attacker->height / 2 >= target->y - target->height / 2 &&
            attacker->y - attacker->height / 2 <= target->y + target->height / 2 &&
            attacker->fight->hit == 0) {
            attacker->fight->hit = 1;
            return 1;
        }
    }
    return 0;
}

void updateKick(rectangle* attacker, rectangle* target){

    if (attacker->fight->kick) {
        // Verifica a colisão do soco
        if (kickCollision(attacker, target)) {
            attacker->fight->collision = 1;
            attacker->fight->life -= HITKICK;
            // Aqui você pode adicionar lógica para reduzir a vida do adversário ou outros efeitos
        }

        // Atualiza o frame do chute
        attacker->fight->frame++;
        if (attacker->fight->frame > 10) {
            attacker->fight->kick = 0;
            attacker->fight->frame = 0;
            attacker->fight->hit = 0;
            attacker->fight->collision = 0;
            attacker->fight->cooldown = 30;
        }
    } else if (attacker->fight->cooldown > 0) attacker->fight->cooldown --;
}


void fightDestroy(rectangle* player){
    free(player->fight);
}

