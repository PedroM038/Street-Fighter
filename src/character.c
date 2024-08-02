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
    newPlayer->staminaStatus = staminaCreate(p);
    newPlayer->control = joystickCreate();
    newPlayer->fight = fightInit(character);
    newPlayer->stop = stopInit(character);
    newPlayer->walking = walkingInit(character);
    newPlayer->jump = jumpInit(character);
    newPlayer->squat = squatInit(character);
    newPlayer->healthStatus = healthInit(character, p);
    newPlayer->dead = deadInit(character);
    if (character == AIKO || character == KIRA){
        newPlayer->specialAttack = specialInit(character);
    }
    return newPlayer;
}

void reInitp1(player* p){
    p->x = 200;
    p->y = YSCREEN - 350;
    p->healthStatus->life = LIFE;
    p->staminaStatus->stamina = STAMINA;
}

void reInitp2(player* p){
    p->x = XSCREEN - 200;
    p->y = YSCREEN - 350;
    p->healthStatus->life = LIFE;
    p->staminaStatus->stamina = STAMINA;
}

void specialDestroy(player* p){
    if (!p->specialAttack) return;
    if (p->hero != KIRA || p->hero != AIKO) return;
    al_destroy_bitmap(p->specialAttack->sprite);
    free(p->specialAttack);
}

special* specialInit (unsigned char hero){
    special* s = malloc(sizeof(special));
    s->inSpecial = 0;
    s->frame = 0;
    s->cooldown = 0;
    s->hit = 0;
    s->actualPicture = 0;
    s->flagActive = 0;
    
    if (hero == AIKO){
        s->maxFrame = 102;
        for (int i = 0; i < 34; i++){
            s->xPicture[i] = i*269;
        }
        s->sprite = al_load_bitmap("media/Aiko/special/specialSprite.png");
        if (!s->sprite){
            fprintf (stderr, "não foi possível carregar o sprite de especial da Aiko");
            exit (EXIT_FAILURE);
        }

    } else if (hero == KIRA){
        s->maxFrame = 156;
        for (int i = 0; i < 52; i++){
            s->xPicture[i] = i*220;
        }
        s->sprite = al_load_bitmap("media/Kira/special/specialSprite.png");
        if (!s->sprite){
            fprintf (stderr, "não foi possível carregar o sprite de especial da Kira");
            exit (EXIT_FAILURE);
        }
    }
    return s;    
}

void deadDestroy(player* p){
    if (!p->dead) return;
    al_destroy_bitmap(p->dead->sprite);
    free (p->dead);
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
        d->sprite = al_load_bitmap("media/Kira/dead/deadSprites.png");
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
        d->sprite = al_load_bitmap("media/Hanzo/dead/deadSprites.png");
        if (!d->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite dead\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (hero == AIKO){
        for (int i = 0; i < 10; i++){
            d->xPicture[i] = i * 269;
        }
        d->actualPicture = 0;
        d->sprite = al_load_bitmap("media/Aiko/dead/deadSprites.png");
        if (!d->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite dead\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (hero == YUNA){
        for (int i = 0; i < 10; i++){
            d->xPicture[i] = i * 333;
        }
        d->actualPicture = 0;
        d->sprite = al_load_bitmap("media/Yuna/dead/deadSprites.png");
        if (!d->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite dead\n");
            exit(EXIT_FAILURE);
        }
    }
    return d;
}

void stopDestroy (player* p){
    if (!p->stop) return;
    al_destroy_bitmap(p->stop->sprite);
    free(p->stop);
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
        a->sprite = al_load_bitmap("media/Kira/stop/stopSprites.png");
        if (!a->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite stop\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (hero == HANZO){
        //insere em um vetor as posicoes x de cada sprite na imagem
        for(int i = 0; i < 8; i++){
            a->xPicture[i] = i * 210;
        }
        a->actualPicture = 0;
        a->sprite = al_load_bitmap("media/Hanzo/stop/stopSprites.png");
        if (!a->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite stop\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (hero == AIKO){
        //insere em um vetor as posicoes x de cada sprite na imagem
        for(int i = 0; i < 12; i++){
            a->xPicture[i] = i * 269;
        }
        a->actualPicture = 0;
        a->sprite = al_load_bitmap("media/Aiko/stop/stopSprites.png");
        if (!a->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite stop\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (hero == YUNA){
        //insere em um vetor as posicoes x de cada sprite na imagem
        for(int i = 0; i < 8; i++){
            a->xPicture[i] = i * 333;
        }
        a->actualPicture = 0;
        a->sprite = al_load_bitmap("media/Yuna/stop/stopSprites.png");
        if (!a->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite stop do hanzo\n");
            exit(EXIT_FAILURE);
        }
    }
    return a;
}

void walkingDestroy(player* p){
    if (!p->walking) return;
    al_destroy_bitmap (p->walking->sprite);
    free (p->walking);
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
        w->sprite = al_load_bitmap("media/Kira/walking/walkingSprites.png");
        if (!w->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite walking\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (hero == HANZO){
        for(int i = 0; i < 18; i++){
            w->xPicture[i] = i * 210;
        }
        w->actualPicture = 0;
        w->sprite = al_load_bitmap("media/Hanzo/walking/walkingSprites.png");
        if (!w->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite walking hanzo\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (hero == AIKO){
        for(int i = 0; i < 20; i++){
            w->xPicture[i] = i * 269;
        }
        w->actualPicture = 0;
        w->sprite = al_load_bitmap("media/Aiko/walking/walkingSprites.png");
        if (!w->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite walking\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (hero == YUNA){
        for(int i = 0; i < 16; i++){
            w->xPicture[i] = i * 333;
        }
        w->actualPicture = 0;
        w->sprite = al_load_bitmap("media/Yuna/walking/walkingSprites.png");
        if (!w->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite walking\n");
            exit(EXIT_FAILURE);
        }
    }

    return w;
}

void jumpDestroy(player* p){
    if (!p->jump) return;
    al_destroy_bitmap (p->jump->sprite);
    free (p->jump);
}

stateJump* jumpInit(unsigned char hero){

    stateJump* j = malloc(sizeof(stateJump));
    j->frame = 0;
    j->isJump = 0;
    j->velocityY = 0;
    j->accelerationY = GRAVITY;
    j->isTop = 0;
    
    if (hero == KIRA){
        j->sprite = al_load_bitmap("media/Kira/jump/jumpSprites.png");
        if (!j->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite jumping\n");
            exit(EXIT_FAILURE);
        }
        for(int i = 0; i < 12; i++){
            j->xPicture[i] = i * 200;
        }

        j->actualPicture = 0;
    }

    else if (hero == HANZO){
        j->sprite = al_load_bitmap("media/Hanzo/jump/jumpSprites.png");
        if (!j->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite jumping Hanzo\n");
            exit(EXIT_FAILURE);
        }
        for(int i = 0; i < 12; i++){
            j->xPicture[i] = i * 210;
        }

        j->actualPicture = 0;
    }

    else if (hero == AIKO){
        j->sprite = al_load_bitmap("media/Aiko/jump/jumpSprites.png");
        if (!j->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite jumping\n");
            exit(EXIT_FAILURE);
        }
        for(int i = 0; i < 10; i++){
            j->xPicture[i] = i * 269;
        }

        j->actualPicture = 0;
    }

    else if (hero == YUNA){
        j->sprite = al_load_bitmap("media/Yuna/jump/jumpSprites.png");
        if (!j->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite jumping\n");
            exit(EXIT_FAILURE);
        }
        for(int i = 0; i < 8; i++){
            j->xPicture[i] = i * 333;
        }

        j->actualPicture = 0;
    }

    return j;
}

void squatDestroy(player* p){
    if (!p->squat) return;
    al_destroy_bitmap (p->squat->sprite);
    free(p->squat);
}

stateSquat* squatInit(unsigned char hero){
    stateSquat* s = malloc(sizeof(stateSquat));
    s->isSquat = 0;
    if (hero == KIRA){
        s->xPicture[0] = 0;
        s->xPicture[1] = 200;
        s->actualPicture = 0;
        s->sprite = al_load_bitmap("media/Kira/squat/squatSprites.png");
        if (!s->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite squat\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (hero == HANZO){
        s->xPicture[0] = 0;
        s->xPicture[1] = 210;
        s->actualPicture = 0;
        s->sprite = al_load_bitmap("media/Hanzo/squat/squatSprites.png");
        if (!s->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite squat hanzo\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (hero == AIKO){
        s->xPicture[0] = 0;
        s->xPicture[1] = 269;
        s->actualPicture = 0;
        s->sprite = al_load_bitmap("media/Aiko/squat/squatSprites.png");
        if (!s->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite squat\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (hero == YUNA){
        s->xPicture[0] = 0;
        s->xPicture[1] = 333;
        s->actualPicture = 0;
        s->sprite = al_load_bitmap("media/Yuna/squat/squatSprites.png");
        if (!s->sprite){
            fprintf(stderr, "Não foi possível carregar o sprite squat\n");
            exit(EXIT_FAILURE);
        }
    }
    return s;
}

void staminaDestroy(player* p){
    if (!p->staminaStatus) return;
    free (p->staminaStatus);
}

staminaPlayer* staminaCreate(unsigned char player){
    staminaPlayer* s = malloc(sizeof(staminaPlayer));
    s->stamina = STAMINA;
    s->yInit = 210;
    s->yEnd = s->yInit + 45;

    if (player == 1) {
        s->xInit = 110;
        s->xEnd = (s->xInit + s->stamina);
    }
    else {
        s->xInit = XSCREEN - 110;
        s->xEnd = (s->xInit - s->stamina);
    }
    return s;
}

void healthDestroy(player* p){
    if (!p->healthStatus) return;
    al_destroy_bitmap (p->healthStatus->picturePlayer);
    free (p->healthStatus);
}

void fightDestroy(player* p){
    if (!p->fight) return;
    al_destroy_bitmap(p->fight->spritePunch);
    al_destroy_bitmap(p->fight->spriteKick);
    free(p->fight);
}

void playerDestroy(player* element){
    
    staminaDestroy(element);
    deadDestroy(element);
    jumpDestroy(element);
    squatDestroy(element);
    healthDestroy(element);
    stopDestroy(element);
    walkingDestroy(element);
    joystickDestroy(element->control);
    fightDestroy(element);
    if (element->hero == KIRA || element->hero == AIKO)
        specialDestroy(element);
    free(element);
}