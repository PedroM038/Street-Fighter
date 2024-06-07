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
    newRectangle->attackPunch = punchInit();
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

fight* punchInit(){
    fight* p = malloc(sizeof(fight));
    p->frame = 0;
    p->hit = 0;
    p->punch = 0;
    p->punchCooldown = 0;
    p->walkBackward = 0;
    p->walkForward = 0;
    p->collision = 0;
    return p;
}

void updatePunch(rectangle* attacker, rectangle* target) {
    if (attacker->attackPunch->punch) {
        // Verifica a colisão do soco
        if (punchCollision(attacker, target)) {
            attacker->attackPunch->collision = 1;
            // Aqui você pode adicionar lógica para reduzir a vida do adversário ou outros efeitos
        }

        // Atualiza o frame do soco
        attacker->attackPunch->frame++;
        if (attacker->attackPunch->frame > 10) {
            attacker->attackPunch->punch = 0;
            attacker->attackPunch->frame = 0;
            attacker->attackPunch->hit = 0;
            attacker->attackPunch->collision = 0;
            attacker->attackPunch->punchCooldown = 30;
        }
    } else if (attacker->attackPunch->punchCooldown > 0) {
        attacker->attackPunch->punchCooldown --;
    }
}

unsigned char punchCollision(rectangle* attacker, rectangle* target) {
    
    // Ajuste os valores conforme necessário para o alcance do soco
    unsigned short punchReach = (attacker->base / 2) + 20;

    if (attacker->x <= target->x){
        attacker->attackPunch->walkForward = 1;
        attacker->attackPunch->walkBackward = 0; 
    }
    else{
        attacker->attackPunch->walkBackward = 1;
        attacker->attackPunch->walkForward = 0;
    }

    if (attacker->attackPunch->punch) {
        if (attacker->attackPunch->walkForward && 
            attacker->x + punchReach >= target->x - target->base / 2 &&
            attacker->x <= target->x + target->base / 2 &&
            attacker->y + attacker->height / 2 >= target->y - target->height / 2 &&
            attacker->y - attacker->height / 2 <= target->y + target->height / 2 &&
            attacker->attackPunch->hit == 0) {
            attacker->attackPunch->hit = 1;
            return 1;
        }

        if (attacker->attackPunch->walkBackward &&
            attacker->x - punchReach <= target->x + target->base / 2 &&
            attacker->x >= target->x - target->base / 2 &&
            attacker->y + attacker->height / 2 >= target->y - target->height / 2 &&
            attacker->y - attacker->height / 2 <= target->y + target->height / 2 &&
            attacker->attackPunch->hit == 0) {
            attacker->attackPunch->hit = 1;
            return 1;
        }
    }
    return 0;
}

void fightDestroy(rectangle* player){
    free(player->attackPunch);
}

