#include "../include/stateMachine.h"
#include <allegro5/allegro_image.h>

void playerMove(player* element, double steps, unsigned short trajectory, unsigned short maxX, unsigned short maxY){

    if (!trajectory){ //left
        if ((element->x - steps*STEP) - element->base/2 >= 0)
            element->x = element->x - steps*STEP;
    }

    else if (trajectory == 1){ //right
        if ((element->x + steps*STEP) + element->base/2 <= maxX) 
            element->x = element->x + steps*STEP;
    }

    else if (trajectory == 2){ //up
        if ((element->y - steps*STEP) - element->height/2 >= 0) 
            element->y = element->y - steps*STEP;
    }

    else if (trajectory == 3){ //down
        if ((element->y + steps*STEP) + element->height/2 <= maxY) 
            element->y = element->y + steps*STEP;
    }
}

unsigned char collision(player* p1, player* p2){

     if (p1->x + p1->base / 2 >= p2->x - p2->base / 2 &&  
        p1->x - p1->base / 2 <= p2->x + p2->base / 2 &&  
        p1->y + p1->height / 2 >= p2->y - p2->height / 2 &&  
        p1->y - p1->height / 2 <= p2->y + p2->height / 2) {  
            return 1;
    }
    return 0;
}

void updateJump(player* playerJump, player* other){
    
    if (playerJump->control->up && playerJump->jump == 0 && playerJump->y == playerJump->yInit) {
        playerJump->jump = 1;
        playerJump->velocityY = -40;
    }

    if (playerJump->jump) {
        playerJump->velocityY += playerJump->accelerationY;
        playerJump->y += playerJump->velocityY;

        if (collision(playerJump, other)) {
            playerJump->y -= playerJump->velocityY;
            playerJump->velocityY = 0; 
            playerJump->isTop = 1;
        }
        else {
            playerJump->isTop = 0;
        }

        if (playerJump->y >= playerJump->yInit) {
            playerJump->y = playerJump->yInit;
            playerJump->jump = 0;
            playerJump->velocityY = 0;
        }
    }
}

void updateStop(player* p){
    if (!p->control->right && !p->control->left && !p->jump && !p->squat){
        p->stop->isStop = 1;
        unsigned short maxFrame = 90;
        if (p->walkForward && p->hero == KIRA) {
            if(p->stop->frame % maxFrame >= 74)
                p->stop->picture = al_load_bitmap("../media/Kira/parado/000.png");
            else if (p->stop->frame % maxFrame >= 58)
                p->stop->picture = al_load_bitmap("../media/Kira/parado/001.png");
            else if (p->stop->frame % maxFrame >= 44)
                p->stop->picture = al_load_bitmap("../media/Kira/parado/002.png");
            else if (p->stop->frame % maxFrame >= 32)
                p->stop->picture = al_load_bitmap("../media/Kira/parado/003.png");
            else if (p->stop->frame % maxFrame >= 16)
                p->stop->picture = al_load_bitmap("../media/Kira/parado/002.png");
            else if (p->stop->frame % maxFrame >= 0)
                p->stop->picture = al_load_bitmap("../media/Kira/parado/001.png");
            
            if (!p->stop->picture){
                fprintf(stderr, "Não foi possível carregar a imagem");
                exit(EXIT_FAILURE);
            }
            
            p->stop->frame += 1;
            if (p->stop->frame >= maxFrame) p->stop->frame = 0;
        } 
        else if (p->walkBackward && p->hero == KIRA) {
            if(p->stop->frame % maxFrame >= 74)
                p->stop->picture = al_load_bitmap("../media/Kira/parado/000B.png");
            else if (p->stop->frame % maxFrame >= 58)
                 p->stop->picture = al_load_bitmap("../media/Kira/parado/001B.png");
            else if (p->stop->frame % maxFrame >= 44)
                p->stop->picture = al_load_bitmap("../media/Kira/parado/002B.png");
            else if (p->stop->frame % maxFrame >= 32)
                p->stop->picture = al_load_bitmap("../media/Kira/parado/003B.png");
            else if (p->stop->frame % maxFrame >= 16)
                p->stop->picture = al_load_bitmap("../media/Kira/parado/002B.png");
            else if (p->stop->frame % maxFrame >= 0)
                p->stop->picture = al_load_bitmap("../media/Kira/parado/001B.png");
        
            if (!p->stop->picture){
                fprintf(stderr, "Não foi possível carregar a imagem");
                 exit(EXIT_FAILURE);
            }
                
            p->stop->frame += 1;
            if (p->stop->frame >= maxFrame) p->stop->frame = 0;
        }
    }
    else{
        p->stop->isStop = 0;
        p->stop->frame = 0;
    }
}

void updatePosition(player* player1, player* player2){

    int prevX, prevY;

    if (player1->x <= player2->x){
        player1->walkBackward = 0;
        player1->walkForward = 1;
        player2->walkBackward = 1;
        player2->walkForward = 0; 
    }
    else{
        player1->walkBackward = 1;
        player1->walkForward = 0;
        player2->walkBackward = 0;
        player2->walkForward = 1;
    }

    prevX = player1->x;
    prevY = player1->y;
    if (player1->control->left) {
        playerMove(player1, 1, 0, XSCREEN, YSCREEN);
        if (collision(player1, player2)) { player1->x = prevX; player1->y = prevY; }
    }

    prevX = player1->x;
    prevY = player1->y;
    if (player1->control->right) {
        playerMove(player1, 1, 1, XSCREEN, YSCREEN);
        if (collision(player1, player2)) { player1->x = prevX; player1->y = prevY; }
    }
    
    updateStop(player1);
    updateJump(player1, player2);
    updatePunch(player1, player2);
    updateKick(player1, player2);

    prevX = player2->x;
    prevY = player2->y;
    if (player2->control->left) {
        playerMove(player2, 1, 0, XSCREEN, YSCREEN);
        if (collision(player1, player2)) { player2->x = prevX; player2->y = prevY; }
    }

    prevX = player2->x;
    prevY = player2->y;
    if (player2->control->right) {
        playerMove(player2, 1, 1, XSCREEN, YSCREEN);
        if (collision(player1, player2)) { player2->x = prevX; player2->y = prevY; }
    }

    updateStop(player2);
    updateJump(player2, player1);
    updatePunch(player2, player1);
    updateKick(player2, player1);

}

unsigned char punchCollision(player* attacker, player* target){
     
    unsigned short punchReach = (attacker->base / 2) + 70;


    if (attacker->fight->punch) {
        if (attacker->walkForward &&
            attacker->x + punchReach >= target->x - target->base / 2 &&
            attacker->x <= target->x + target->base / 2 &&
            attacker->y + attacker->height / 2 >= target->y - target->height / 2 &&
            attacker->y - attacker->height / 2 <= target->y + target->height / 2 &&
            attacker->fight->hit == 0) {
            attacker->fight->hit = 1;
            return 1;
        }

        if (attacker->walkBackward &&
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

void updatePunch(player* attacker, player* target){

     if (attacker->fight->punch) {
        if (punchCollision(attacker, target)) {
            attacker->fight->collision = 1;
            attacker->fight->life -= HITPUNCH;
        }

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

unsigned char kickCollision(player* attacker, player* target){

    unsigned short kickReach = (attacker->base / 2) + 70;

    if (attacker->fight->kick) {
        if (attacker->walkForward && 
            attacker->x + kickReach >= target->x - target->base / 2 &&
            attacker->x <= target->x + target->base / 2 &&
            attacker->y + attacker->height / 2 >= target->y - target->height / 2 &&
            attacker->y - attacker->height / 2 <= target->y + target->height / 2 &&
            attacker->fight->hit == 0) {
            attacker->fight->hit = 1;
            return 1;
        }

        if (attacker->walkBackward &&
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

void updateKick(player* attacker, player* target){
    if (attacker->fight->kick) {
        if (kickCollision(attacker, target)) {
            attacker->fight->collision = 1;
            attacker->fight->life -= HITKICK;
        }

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
