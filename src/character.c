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
    /*newPlayer->jump = 0;
    newPlayer->isTop = 0;
    newPlayer->velocityY = 0;
    newPlayer->accelerationY = GRAVITY;*/
    newPlayer->control = joystickCreate();
    newPlayer->fight = fightInit();
    newPlayer->stop = stopInit();
    newPlayer->walking = walkingInit();
    newPlayer->jump = jumpInit();
    return newPlayer;
}

stateStop* stopInit(){
    stateStop* a = malloc(sizeof(stateStop));
    a->frame = 0;
    a->isStop = 1;
    return a;
}

stateWalking* walkingInit(){
    stateWalking* a = malloc(sizeof(stateWalking));
    // Carregar as imagens de caminhada para frente
    char framePath[100];
    for (int i = 0; i < 12; i++) {
        snprintf(framePath, sizeof(framePath), "../media/Kira/caminhando/%03d.png", i);
        a->walkForwardFrames[i] = al_load_bitmap(framePath);
        if (!a->walkForwardFrames[i]) {
            fprintf(stderr, "Não foi possível carregar a imagem %03d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Carregar as imagens de caminhada para trás
    for (int i = 0; i < 12; i++) {
        snprintf(framePath, sizeof(framePath), "../media/Kira/caminhando/%03dB.png", i);
        a->walkBackwardFrames[i] = al_load_bitmap(framePath);
        if (!a->walkBackwardFrames[i]) {
            fprintf(stderr, "Não foi possível carregar a imagem %03dB\n", i);
            exit(EXIT_FAILURE);
        }
    }

    a->frame = 0;
    a->isWalking = 0;
    return a;
}

stateJump* jumpInit(){
    stateJump* j = malloc(sizeof(stateJump));

    char framePath[100];
    for (int i = 0; i < 6; i++){
        snprintf(framePath, sizeof(framePath), "../media/Kira/pulo/%03d.png", i);
        j->walkForwardFrames[i] = al_load_bitmap(framePath);
        if (!j->walkForwardFrames[i]) {
            fprintf(stderr, "Não foi possível carregar a imagem %03d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 6; i++){
        snprintf(framePath, sizeof(framePath), "../media/Kira/pulo/%03dB.png", i);
        j->walkBackwardFrames[i] = al_load_bitmap(framePath);
        if (!j->walkBackwardFrames[i]) {
            fprintf(stderr, "Não foi possível carregar a imagem %03d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    j->frame = 0;
    j->isJump = 0;
    j->velocityY = 0;
    j->accelerationY = GRAVITY;
    j->isTop = 0;
    return j;
}

void playerDestroy(player* element){
    
    // Libere a memória alocada para as imagens ao final do programa
    for (int i = 0; i < 12; i++) {
        al_destroy_bitmap(element->walking->walkForwardFrames[i]);
        al_destroy_bitmap(element->walking->walkBackwardFrames[i]);
    }
    if (element->stop->picture) free(element->stop->picture);
    free(element->stop);
    free(element->walking);
    joystickDestroy(element->control);
    fightDestroy(element->fight);
    free(element);
}