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

void updateJumpFrame(player* p) {
    unsigned short maxFrame = 48;
    unsigned short interval = 8;
    
    if(p->hero == KIRA && p->walkForward){

        if(p->control->right || (!p->control->right && !p->control->left)){

            if(p->jump->frame % maxFrame >= maxFrame - interval*1)
                p->jump->actualPicture = 5;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*2)
                p->jump->actualPicture = 4;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*3)
                p->jump->actualPicture = 3;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*4)
                p->jump->actualPicture = 2;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*5)
                p->jump->actualPicture = 1;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*6)
                p->jump->actualPicture = 0;

            p->jump->frame += 1;
            if (p->jump->frame >= maxFrame) p->jump->frame = 0;
        }
        else{
            if(p->jump->frame % maxFrame >= maxFrame - interval*1)
                p->jump->actualPicture = 11;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*2)
                p->jump->actualPicture = 10;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*3)
                p->jump->actualPicture = 9;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*4)
                p->jump->actualPicture = 8;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*5)
                p->jump->actualPicture = 7;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*6)
                p->jump->actualPicture = 6;

            p->jump->frame += 1;
            if (p->jump->frame >= maxFrame) p->jump->frame = 0;
        }

    } else if (p->hero == KIRA && p->walkBackward) {
            if(p->control->left || (!p->control->right && !p->control->left)){

                if(p->jump->frame % maxFrame >= maxFrame - interval*1)
                    p->jump->actualPicture = 11;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*2)
                    p->jump->actualPicture = 10;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*3)
                    p->jump->actualPicture = 9;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*4)
                    p->jump->actualPicture = 8;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*5)
                    p->jump->actualPicture = 7;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*6)
                    p->jump->actualPicture = 6;

                p->jump->frame += 1;
                if (p->jump->frame >= maxFrame) p->jump->frame = 0;
            }
            else {
                if(p->jump->frame % maxFrame >= maxFrame - interval*1)
                    p->jump->actualPicture = 5;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*2)
                    p->jump->actualPicture = 4;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*3)
                    p->jump->actualPicture = 3;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*4)
                    p->jump->actualPicture = 2;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*5)
                    p->jump->actualPicture = 1;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*6)
                    p->jump->actualPicture = 0;

                p->jump->frame += 1;
                if (p->jump->frame >= maxFrame) p->jump->frame = 0;
            }
    }
    if(p->hero == HANZO && p->walkForward){

        if(p->control->right || (!p->control->right && !p->control->left)){

            if(p->jump->frame % maxFrame >= maxFrame - interval*1)
                p->jump->actualPicture = 5;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*2)
                p->jump->actualPicture = 4;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*3)
                p->jump->actualPicture = 3;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*4)
                p->jump->actualPicture = 2;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*5)
                p->jump->actualPicture = 1;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*6)
                p->jump->actualPicture = 0;

            p->jump->frame += 1;
            if (p->jump->frame >= maxFrame) p->jump->frame = 0;
        }
        else{

            if(p->jump->frame % maxFrame >= maxFrame - interval*1)
                p->jump->actualPicture = 11;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*2)
                p->jump->actualPicture = 10;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*3)
                p->jump->actualPicture = 9;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*4)
                p->jump->actualPicture = 8;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*5)
                p->jump->actualPicture = 7;
            else if (p->jump->frame % maxFrame >= maxFrame - interval*6)
                p->jump->actualPicture = 6;

            p->jump->frame += 1;
            if (p->jump->frame >= maxFrame) p->jump->frame = 0;
        }

    } else if (p->hero == HANZO && p->walkBackward) {
            if(p->control->left || (!p->control->right && !p->control->left)){

                if(p->jump->frame % maxFrame >= maxFrame - interval*1)
                    p->jump->actualPicture = 11;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*2)
                    p->jump->actualPicture = 10;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*3)
                    p->jump->actualPicture = 9;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*4)
                    p->jump->actualPicture = 8;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*5)
                    p->jump->actualPicture = 7;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*6)
                    p->jump->actualPicture = 6;

                p->jump->frame += 1;
                if (p->jump->frame >= maxFrame) p->jump->frame = 0;
            }
            else {
                if(p->jump->frame % maxFrame >= maxFrame - interval*1)
                    p->jump->actualPicture = 5;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*2)
                    p->jump->actualPicture = 4;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*3)
                    p->jump->actualPicture = 3;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*4)
                    p->jump->actualPicture = 2;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*5)
                    p->jump->actualPicture = 1;
                else if (p->jump->frame % maxFrame >= maxFrame - interval*6)
                    p->jump->actualPicture = 0;

                p->jump->frame += 1;
                if (p->jump->frame >= maxFrame) p->jump->frame = 0;
            }
    }
}

void updateFrameSquat(player* p){
    if (p->walkForward && p->hero == KIRA)
        p->squat->actualPicture = 0;
    else if (p->walkBackward && p->hero == KIRA)
        p->squat->actualPicture = 1;
    else if (p->walkForward && p->hero == HANZO)
        p->squat->actualPicture = 0;
    else if (p->walkBackward && p->hero == HANZO)
        p->squat->actualPicture = 1;
}

void updateFrameStop(player* p){
    if (p->walkForward && p->hero == KIRA) {
        unsigned short maxFrame = 170;
        unsigned short interval = 10;
        if(p->stop->frame % maxFrame >= maxFrame - interval*1)
            p->stop->actualPicture = 0;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*2)
            p->stop->actualPicture = 4;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*3)
            p->stop->actualPicture = 5;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*4)
            p->stop->actualPicture = 6;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*5)
            p->stop->actualPicture = 7;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*6)
            p->stop->actualPicture = 8;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*7)
            p->stop->actualPicture = 7;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*8)
            p->stop->actualPicture = 6;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*9)
            p->stop->actualPicture = 5;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*10)
            p->stop->actualPicture = 4;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*11)
            p->stop->actualPicture = 0;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*12)
            p->stop->actualPicture = 1;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*13)
            p->stop->actualPicture = 2;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*14)
            p->stop->actualPicture = 3;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*15)
            p->stop->actualPicture = 2;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*16)
            p->stop->actualPicture = 1;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*17)
            p->stop->actualPicture = 0;
            
        p->stop->frame += 1;
        if (p->stop->frame >= maxFrame) p->stop->frame = 0;
    }
    else if (p->walkBackward && p->hero == KIRA){
        unsigned short maxFrame = 170;
        unsigned short interval = 10;
        if(p->stop->frame % maxFrame >= maxFrame - interval*1)
            p->stop->actualPicture = 9;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*2)
            p->stop->actualPicture = 13;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*3)
            p->stop->actualPicture = 14;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*4)
            p->stop->actualPicture = 15;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*5)
            p->stop->actualPicture = 16;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*6)
            p->stop->actualPicture = 17;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*7)
            p->stop->actualPicture = 16;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*8)
            p->stop->actualPicture = 15;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*9)
            p->stop->actualPicture = 14;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*10)
            p->stop->actualPicture = 13;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*11)
            p->stop->actualPicture = 9;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*12)
            p->stop->actualPicture = 10;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*13)
            p->stop->actualPicture = 11;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*14)
            p->stop->actualPicture = 12;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*15)
            p->stop->actualPicture = 11;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*16)
            p->stop->actualPicture = 10;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*17)
            p->stop->actualPicture = 9;
            
        p->stop->frame += 1;
        if (p->stop->frame >= maxFrame) p->stop->frame = 0;
    }
    else if (p->hero == HANZO && p->walkForward){
        unsigned short maxFrame = 40;
        unsigned short interval = 10;
        if(p->stop->frame % maxFrame >= maxFrame - interval*1)
            p->stop->actualPicture = 3;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*2)
            p->stop->actualPicture = 2;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*3)
            p->stop->actualPicture = 1;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*4)
            p->stop->actualPicture = 0;

        p->stop->frame += 1;
        if (p->stop->frame >= maxFrame) p->stop->frame = 0;
    }
    else if (p->hero == HANZO && p->walkBackward){
        unsigned short maxFrame = 48;
        unsigned short interval = 12;
        if(p->stop->frame % maxFrame >= maxFrame - interval*1)
            p->stop->actualPicture = 7;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*2)
            p->stop->actualPicture = 6;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*3)
            p->stop->actualPicture = 5;
        else if (p->stop->frame % maxFrame >= maxFrame - interval*4)
            p->stop->actualPicture = 4;

        p->stop->frame += 1;
        if (p->stop->frame >= maxFrame) p->stop->frame = 0;
    }
}

// Função para atualizar o frame do jogador
void updateWalkingFrame(player* p) {
    if (p->control->right && p->hero == KIRA) {
        unsigned short maxFrame = 70;
        unsigned short interval = 7;
        if(p->walking->frame % maxFrame >= maxFrame - interval*1)
            p->walking->actualPicture = 9;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*2)
            p->walking->actualPicture = 8;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*3)
            p->walking->actualPicture = 7;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*4)
            p->walking->actualPicture = 6;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*5)
            p->walking->actualPicture = 5;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*6)
            p->walking->actualPicture = 4;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*7)
            p->walking->actualPicture = 3;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*8)
            p->walking->actualPicture = 2;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*9)
            p->walking->actualPicture = 1;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*10)
            p->walking->actualPicture = 0;

        p->walking->frame += 1;
        if (p->walking->frame >= maxFrame) p->walking->frame = 0;
    }

    else if (p->control->left && p->hero == KIRA){
        unsigned short maxFrame = 70;
        unsigned short interval = 7;
        if(p->walking->frame % maxFrame >= maxFrame - interval*1)
            p->walking->actualPicture = 19;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*2)
            p->walking->actualPicture = 18;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*3)
            p->walking->actualPicture = 17;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*4)
            p->walking->actualPicture = 16;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*5)
            p->walking->actualPicture = 15;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*6)
            p->walking->actualPicture = 14;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*7)
            p->walking->actualPicture = 13;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*8)
            p->walking->actualPicture = 12;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*9)
            p->walking->actualPicture = 11;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*10)
            p->walking->actualPicture = 10;

        p->walking->frame += 1;
        if (p->walking->frame >= maxFrame) p->walking->frame = 0;
    }

    else if (p->hero == HANZO && p->control->left ){
        unsigned short maxFrame = 63;
        unsigned short interval = 7;
        if(p->walking->frame % maxFrame >= maxFrame - interval*1)
            p->walking->actualPicture = 11;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*2)
            p->walking->actualPicture = 10;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*3)
            p->walking->actualPicture = 11;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*4)
            p->walking->actualPicture = 12;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*5)
            p->walking->actualPicture = 13;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*6)
            p->walking->actualPicture = 14;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*7)
            p->walking->actualPicture = 15;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*8)
            p->walking->actualPicture = 16;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*9)
            p->walking->actualPicture = 17;;

        p->walking->frame += 1;
        if (p->walking->frame >= maxFrame) p->walking->frame = 0;
    }

    else if (p->hero == HANZO && p->control->right ){
        unsigned short maxFrame = 63;
        unsigned short interval = 7;
        if(p->walking->frame % maxFrame >= maxFrame - interval*1)
            p->walking->actualPicture = 2;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*2)
            p->walking->actualPicture = 1;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*3)
            p->walking->actualPicture = 2;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*4)
            p->walking->actualPicture = 3;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*5)
            p->walking->actualPicture = 4;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*6)
            p->walking->actualPicture = 5;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*7)
            p->walking->actualPicture = 6;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*8)
            p->walking->actualPicture = 7;
        else if (p->walking->frame % maxFrame >= maxFrame - interval*9)
            p->walking->actualPicture = 8;;

        p->walking->frame += 1;
        if (p->walking->frame >= maxFrame) p->walking->frame = 0;
    }
}

void updateFramePunch(player* p){
    if (p->hero == KIRA && p->walkForward){
        unsigned short maxFrame = 42;
        unsigned short interval = 7;
        if(p->fight->frame % maxFrame >= maxFrame - interval*1)
            p->fight->actualPicturePunch = 5;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*2)
            p->fight->actualPicturePunch = 4;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*3)
            p->fight->actualPicturePunch = 3;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*4)
            p->fight->actualPicturePunch = 2;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*5)
            p->fight->actualPicturePunch = 1;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*6)
            p->fight->actualPicturePunch = 0;
    }
    else if (p->hero == KIRA && p->walkBackward){
        unsigned short maxFrame = 42;
        unsigned short interval = 7;
        if(p->fight->frame % maxFrame >= maxFrame - interval*1)
            p->fight->actualPicturePunch = 11;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*2)
            p->fight->actualPicturePunch = 10;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*3)
            p->fight->actualPicturePunch = 9;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*4)
            p->fight->actualPicturePunch = 8;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*5)
            p->fight->actualPicturePunch = 7;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*6)
            p->fight->actualPicturePunch = 6;
    }
    else if (p->hero == HANZO && p->walkForward){
        unsigned short maxFrame = p->fight->totalFrame;
        unsigned short interval = 6;
        if(p->fight->frame % maxFrame >= maxFrame - interval*1)
            p->fight->actualPicturePunch = 9;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*2)
            p->fight->actualPicturePunch = 8;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*3)
            p->fight->actualPicturePunch = 7;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*4)
            p->fight->actualPicturePunch = 6;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*5)
            p->fight->actualPicturePunch = 5;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*6)
            p->fight->actualPicturePunch = 4;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*7)
            p->fight->actualPicturePunch = 3;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*8)
            p->fight->actualPicturePunch = 2;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*9)
            p->fight->actualPicturePunch = 1;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*10)
            p->fight->actualPicturePunch = 0;
    }
    else if (p->hero == HANZO && p->walkBackward){
        unsigned short maxFrame = p->fight->totalFrame;
        unsigned short interval = 6;
        if(p->fight->frame % maxFrame >= maxFrame - interval*1)
            p->fight->actualPicturePunch = 19;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*2)
            p->fight->actualPicturePunch = 18;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*3)
            p->fight->actualPicturePunch = 17;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*4)
            p->fight->actualPicturePunch = 16;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*5)
            p->fight->actualPicturePunch = 15;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*6)
            p->fight->actualPicturePunch = 14;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*7)
            p->fight->actualPicturePunch = 13;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*8)
            p->fight->actualPicturePunch = 12;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*9)
            p->fight->actualPicturePunch = 11;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*10)
            p->fight->actualPicturePunch = 10;
    }
}


void updateFrameKick(player* p){
    unsigned short maxFrame = 49;
    unsigned short interval = 7;
    if (p->hero == KIRA && p->walkForward){
        unsigned short maxFrame = 49;
        unsigned short interval = 7;
        if(p->fight->frame % maxFrame >= maxFrame - interval*1)
            p->fight->actualPictureKick = 6;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*2)
            p->fight->actualPictureKick = 5;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*3)
            p->fight->actualPictureKick = 4;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*4)
            p->fight->actualPictureKick = 3;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*5)
            p->fight->actualPictureKick = 2;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*6)
            p->fight->actualPictureKick = 1;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*7)
            p->fight->actualPictureKick = 0;
    }

    else if (p->hero == KIRA && p->walkBackward){
        unsigned short maxFrame = 49;
        unsigned short interval = 7;
        if(p->fight->frame % maxFrame >= maxFrame - interval*1)
            p->fight->actualPictureKick = 13;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*2)
            p->fight->actualPictureKick = 12;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*3)
            p->fight->actualPictureKick = 11;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*4)
            p->fight->actualPictureKick = 10;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*5)
            p->fight->actualPictureKick = 9;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*6)
            p->fight->actualPictureKick = 8;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*7)
            p->fight->actualPictureKick = 7;
    }
    else if (p->hero == HANZO && p->walkForward){
        unsigned short maxFrame = 65;
        unsigned short interval = 5;
        if(p->fight->frame % maxFrame >= maxFrame - interval*1)
            p->fight->actualPictureKick = 12;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*2)
            p->fight->actualPictureKick = 11;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*3)
            p->fight->actualPictureKick = 10;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*4)
            p->fight->actualPictureKick = 9;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*5)
            p->fight->actualPictureKick = 8;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*6)
            p->fight->actualPictureKick = 7;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*7)
            p->fight->actualPictureKick = 6;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*8)
            p->fight->actualPictureKick = 5;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*9)
            p->fight->actualPictureKick = 4;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*10)
            p->fight->actualPictureKick = 3;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*11)
            p->fight->actualPictureKick = 2;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*12)
            p->fight->actualPictureKick = 1;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*13)
            p->fight->actualPictureKick = 0;
    }
    else if (p->hero == HANZO && p->walkBackward){
        unsigned short maxFrame = 65;
        unsigned short interval = 5;
        if(p->fight->frame % maxFrame >= maxFrame - interval*1)
            p->fight->actualPictureKick = 25;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*2)
            p->fight->actualPictureKick = 24;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*3)
            p->fight->actualPictureKick = 23;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*4)
            p->fight->actualPictureKick = 22;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*5)
            p->fight->actualPictureKick = 21;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*6)
            p->fight->actualPictureKick = 20;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*7)
            p->fight->actualPictureKick = 19;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*8)
            p->fight->actualPictureKick = 18;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*9)
            p->fight->actualPictureKick = 17;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*10)
            p->fight->actualPictureKick = 16;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*11)
            p->fight->actualPictureKick = 15;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*12)
            p->fight->actualPictureKick = 14;
        else if (p->fight->frame % maxFrame >= maxFrame - interval*13)
            p->fight->actualPictureKick = 13;
    }
}

void updatePosition(player* player1, player* player2) {
    int prevX, prevY;
    unsigned short maxFrame = 96;

    // Determinar se os jogadores estão caminhando para frente ou para trás
    if (player1->x <= player2->x) {
        player1->walkBackward = 0;
        player1->walkForward = 1;
        player2->walkBackward = 1;
        player2->walkForward = 0;
    } else {
        player1->walkBackward = 1;
        player1->walkForward = 0;
        player2->walkBackward = 0;
        player2->walkForward = 1;
    }

    // Atualizar posição e animação do Player 1
    prevX = player1->x;
    prevY = player1->y;
    if (player1->control->left && !player1->fight->punch  && !player1->fight->kick && !player1->control->right) {
        playerMove(player1, 1, 0, XSCREEN, YSCREEN);
        if (collision(player1, player2)) {
            player1->x = prevX;
            player1->y = prevY;
        }
        player1->walking->isWalking = 1;
        if (!player1->jump->isJump && !player1->squat->isSquat)
                updateWalkingFrame(player1);

    } else if (player1->control->right && !player1->fight->punch && !player1->fight->kick && !player1->control->left) {
        playerMove(player1, 1, 1, XSCREEN, YSCREEN);
        if (collision(player1, player2)) {
            player1->x = prevX;
            player1->y = prevY;
        }
        player1->walking->isWalking = 1;
        if (!player1->jump->isJump && !player1->squat->isSquat)
            updateWalkingFrame(player1);
    } else {
        player1->walking->isWalking = 0;
        player1->walking->frame = 0;
    }

    // Atualizar outros estados do Player 1
    updateStop(player1);
    updateJump(player1, player2);
    updateSquat(player1, player2);
    updateKick(player1, player2);
    updatePunch(player1, player2);

    // Atualizar posição e animação do Player 2
    prevX = player2->x;
    prevY = player2->y;
    if (player2->control->left && !player2->fight->punch && !player2->fight->kick && !player2->control->right) {
        playerMove(player2, 1, 0, XSCREEN, YSCREEN);
        if (collision(player2, player1)) {
            player2->x = prevX;
            player2->y = prevY;
        }
        player2->walking->isWalking = 1;
        if (!player2->jump->isJump && !player2->squat->isSquat)
            updateWalkingFrame(player2);

    } else if (player2->control->right && !player2->fight->punch && !player2->fight->kick && !player2->control->left) {
        playerMove(player2, 1, 1, XSCREEN, YSCREEN);
        if (collision(player2, player1)) {
            player2->x = prevX;
            player2->y = prevY;
        }
        player2->walking->isWalking = 1;
        if (!player2->jump->isJump && !player2->squat->isSquat)
            updateWalkingFrame(player2);
    } else {
        player2->walking->isWalking = 0;
        player2->walking->frame = 0;
    }

    // Atualizar outros estados do Player 2
    updateStop(player2);
    updateJump(player2, player1);
    updateSquat(player2, player1);
    updateKick(player2, player1);
    updatePunch(player2, player1);
}

unsigned char punchCollision(player* attacker, player* target){
     
    unsigned short punchReach = (attacker->base / 2) + 220;

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

unsigned char kickCollision(player* attacker, player* target){

    unsigned short kickReach = (attacker->base / 2) + 220;

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

void updateJump(player* playerJump, player* other){
    
    if (playerJump->control->up && playerJump->jump->isJump == 0 && playerJump->y == playerJump->yInit) {
        playerJump->jump->isJump = 1;
        playerJump->jump->velocityY = -40;
    }

    if (playerJump->jump->isJump) {
        playerJump->jump->velocityY += playerJump->jump->accelerationY;
        playerJump->y += playerJump->jump->velocityY;

        if (collision(playerJump, other)) {
            playerJump->y -= playerJump->jump->velocityY;
            playerJump->jump->velocityY = 0; 
            playerMove(playerJump, STEP, 0, XSCREEN, YSCREEN);
            playerMove(other, STEP, 1, XSCREEN, YSCREEN);
            playerJump->jump->isTop = 1;
        }
        else {
            playerJump->jump->isTop = 0;
            updateJumpFrame(playerJump);
        }

        if (playerJump->y >= playerJump->yInit) {
            playerJump->y = playerJump->yInit;
            playerJump->jump->isJump = 0;
            playerJump->jump->velocityY = 0;
            playerJump->jump->frame = 0;
        }
    }
}

void updateSquat(player* s, player* player2){
    if (s->control->down && !s->control->left && !s->control->right && !s->jump->isJump){
        s->squat->isSquat = 1;
        updateFrameSquat (s);
    } else {
        s->squat->isSquat = 0;
    } 
}

void updateStop(player* p){
    if (((!p->control->right && !p->control->left) || (p->control->right && p->control->left)) && !p->jump->isJump && !p->squat->isSquat && !p->fight->punch
        && !p->fight->kick){
        p->stop->isStop = 1;
        updateFrameStop(p);
       
    } else {
        p->stop->isStop = 0;
        p->stop->frame = 0;
    }
}


void updatePunch(player* attacker, player* target){

     if (attacker->fight->punch) {
        attacker->fight->kick = 0;
        if (punchCollision(attacker, target)) {
            attacker->fight->collision = 1;
            attacker->fight->life -= HITPUNCH;
        }
        updateFramePunch(attacker);
        attacker->fight->frame++;
        if (attacker->fight->frame > attacker->fight->totalFrame) {
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

void updateKick(player* attacker, player* target){
    if (attacker->fight->kick) {
        attacker->fight->punch = 0;
        if (kickCollision(attacker, target)) {
            attacker->fight->collision = 1;
            attacker->fight->life -= HITKICK;
        }
        updateFrameKick(attacker);
        attacker->fight->frame++;
        if (attacker->fight->frame > attacker->fight->totalKick) {
            attacker->fight->kick = 0;
            attacker->fight->frame = 0;
            attacker->fight->hit = 0;
            attacker->fight->collision = 0;
            attacker->fight->cooldown = attacker->fight->totalCooldown;
        }
    } else if (attacker->fight->cooldown > 0) attacker->fight->cooldown --;
}