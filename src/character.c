#include "../include/character.h"
#include <allegro5/allegro_image.h>

player* playerInit(unsigned char character, unsigned short base, unsigned short height, unsigned short x, 
    unsigned short y, unsigned short maxX, unsigned short maxY, unsigned char p){
    
    if ((x - base/2 < 0) || (x + base/2 > maxX) || (y - height/2 < 0) || (y + height/2 > maxY)) return NULL;

    player *newPlayer = (player*) malloc(sizeof(player));
    newPlayer->hero = character;
    newPlayer->base = base;
    newPlayer->height = height;
    newPlayer->xInit = x;
    newPlayer->yInit = y;
    newPlayer->x = x;
    newPlayer->y = y;
    newPlayer->wins = 0;
    newPlayer->cooldown = 0;
    newPlayer->control = joystickCreate();
    newPlayer->fight = fightInit(character);
    newPlayer->stop = stopInit(character);
    newPlayer->walking = walkingInit(character);
    newPlayer->jump = jumpInit(character);
    newPlayer->squat = squatInit(character);
    newPlayer->healthStatus = healthInit(character, p);
    newPlayer->dead = deadInit(character);
    return newPlayer;
}

void reInitp1(player* p){
    p->x = 200;
    p->y = YSCREEN - 350;
    p->healthStatus->life = LIFE;
}

void reInitp2(player* p){
    p->x = XSCREEN - 200;
    p->y = YSCREEN - 350;
    p->healthStatus->life = LIFE;
}

stateDead* deadInit(unsigned char hero){
    stateDead* d = malloc(sizeof(stateDead));
    d->frame = 0;
    d->isDead = 0;
    d->cooldown = 180;
    if (hero == KIRA){
        for (int i = 0; i < 10; i++){
            d->xPicture[i] = i * 200;
        }
        d->actualPicture = 0;
        d->sprite = al_load_bitmap("../media/Kira/dead/deadSprites.png");
        if (!d->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite dead\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (hero == HANZO){
        for (int i = 0; i < 10; i++){
            d->xPicture[i] = i * 210;
        }
        d->actualPicture = 0;
        d->sprite = al_load_bitmap("../media/Hanzo/dead/deadSprites.png");
        if (!d->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite dead\n");
            exit(EXIT_FAILURE);
        }
    }
    return d;
}

stateStop* stopInit(unsigned char hero){
    stateStop* a = malloc(sizeof(stateStop));
    a->frame = 0;
    a->isStop = 1;
    if (hero == KIRA){
        //insere em um vetor as posicoes x de cada sprite na imagem
        for(int i = 0; i < 18; i++){
            a->xPicture[i] = i * 200;
        }
        a->actualPicture = 0;
        a->sprite = al_load_bitmap("../media/Kira/stop/stopSprites.png");
        if (!a->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite stop\n");
            exit(EXIT_FAILURE);
        }
    }
    if (hero == HANZO){
        //insere em um vetor as posicoes x de cada sprite na imagem
        for(int i = 0; i < 8; i++){
            a->xPicture[i] = i * 210;
        }
        a->actualPicture = 0;
        a->sprite = al_load_bitmap("../media/Hanzo/stop/stopSprites.png");
        if (!a->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite stop do hanzo\n");
            exit(EXIT_FAILURE);
        }
    }
    return a;
}

stateWalking* walkingInit(unsigned char hero){
    stateWalking* w = malloc(sizeof(stateWalking));
    w->frame = 0;
    w->isWalking = 0;
    if (hero == KIRA){
        for(int i = 0; i < 20; i++){
            w->xPicture[i] = i * 200;
        }
        w->actualPicture = 0;
        w->sprite = al_load_bitmap("../media/Kira/walking/walkingSprites.png");
        if (!w->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite walking\n");
            exit(EXIT_FAILURE);
        }
    }
    if (hero == HANZO){
        for(int i = 0; i < 18; i++){
            w->xPicture[i] = i * 210;
        }
        w->actualPicture = 0;
        w->sprite = al_load_bitmap("../media/Hanzo/walking/walkingSprites.png");
        if (!w->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite walking hanzo\n");
            exit(EXIT_FAILURE);
        }
    }

    return w;
}

stateJump* jumpInit(unsigned char hero){

    stateJump* j = malloc(sizeof(stateJump));
    j->frame = 0;
    j->isJump = 0;
    j->velocityY = 0;
    j->accelerationY = GRAVITY;
    j->isTop = 0;
    
    if (hero == KIRA){
        j->sprite = al_load_bitmap("../media/Kira/jump/jumpSprites.png");
        if (!j->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite jumping\n");
            exit(EXIT_FAILURE);
        }
        for(int i = 0; i < 12; i++){
            j->xPicture[i] = i * 200;
        }

        j->actualPicture = 0;
    }

    if (hero == HANZO){
        j->sprite = al_load_bitmap("../media/Hanzo/jump/jumpSprites.png");
        if (!j->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite jumping Hanzo\n");
            exit(EXIT_FAILURE);
        }
        for(int i = 0; i < 12; i++){
            j->xPicture[i] = i * 210;
        }

        j->actualPicture = 0;
    }

    return j;
}

stateSquat* squatInit(unsigned char hero){
    stateSquat* s = malloc(sizeof(stateSquat));
    s->isSquat = 0;
    if (hero == KIRA){
        s->xPicture[0] = 0;
        s->xPicture[1] = 200;
        s->actualPicture = 0;
        s->sprite = al_load_bitmap("../media/Kira/squat/squatSprites.png");
        if (!s->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite squat\n");
            exit(EXIT_FAILURE);
        }
    }
    if (hero == HANZO){
        s->xPicture[0] = 0;
        s->xPicture[1] = 210;
        s->actualPicture = 0;
        s->sprite = al_load_bitmap("../media/Hanzo/squat/squatSprites.png");
        if (!s->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite squat hanzo\n");
            exit(EXIT_FAILURE);
        }
    }
    return s;
}

void playerDestroy(player* element){
    
    //destruit bitmap dead
    //destroir bitmap stop
    //destruir bitmap walking
    //destruir bitmap jump
    //destruir bitmap squat
    //destruir struct health
    free(element->stop);
    free(element->walking);
    joystickDestroy(element->control);
    fightDestroy(element->fight);
    free(element);
}