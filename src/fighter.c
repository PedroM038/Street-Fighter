#include "../include/fighter.h"
#include "../include/character.h"

attack* fightInit(unsigned char hero){
    attack* p = malloc(sizeof(attack));
    p->frame = 0;
    p->hit = 0;
    p->punch = 0;
    p->kick = 0;
    p->cooldown = 0;
    p->collision = 0;
    if (hero == KIRA){
        p->spritePunch = al_load_bitmap("media/Kira/basicAttack/basicAttack.png");
        if (!p->spritePunch){
            fprintf(stderr, "Não foi possível carregar o sprite basicAttack\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 12; i++){
            p->xPicturePunch[i] = 200*i;
        }
        p->actualPicturePunch = 0;

        p->spriteKick = al_load_bitmap("media/Kira/kick/kickSprites.png");
        if (!p->spriteKick){
            fprintf(stderr, "Não foi possível carregar o sprite kick\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 14; i++){
            p->xPictureKick[i] = 200*i;
        }
        p->actualPictureKick = 0;
        p->totalFrame = 42;
        p->totalCooldown = 30;
        p->totalKick = 49;
    }
    else if (hero == HANZO){
        p->spritePunch = al_load_bitmap("media/Hanzo/basicAttack/basicAttackSprites.png");
        if (!p->spritePunch){
            fprintf(stderr, "Não foi possível carregar o sprite basicAttack hanzo\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 20; i++){
            p->xPicturePunch[i] = 210*i;
        }
        p->actualPicturePunch = 0;
        p->totalFrame = 60;

        p->spriteKick = al_load_bitmap("media/Hanzo/kick/kickSprites.png");
        if (!p->spriteKick){
            fprintf(stderr, "Não foi possível carregar o sprite kick hanzo\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 26; i++){
            p->xPictureKick[i] = 210*i;
        }
        p->actualPictureKick = 0;
        p->totalCooldown = 60;
        p->totalKick = 65;
    }
    else if (hero == AIKO){
        p->spritePunch = al_load_bitmap("media/Aiko/basicAttack/basicAttackSprites.png");
        if (!p->spritePunch){
            fprintf(stderr, "Não foi possível carregar o sprite basicAttack\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 16; i++){
            p->xPicturePunch[i] = 269*i;
        }
        p->actualPicturePunch = 0;
        p->totalFrame = 60;

        p->spriteKick = al_load_bitmap("media/Aiko/kick/kickSprites.png");
        if (!p->spriteKick){
            fprintf(stderr, "Não foi possível carregar o sprite kick\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 10; i++){
            p->xPictureKick[i] = 269*i;
        }
        p->actualPictureKick = 0;
        p->totalCooldown = 60;
        p->totalKick = 30;
    }
    else if (hero == YUNA){
        p->spritePunch = al_load_bitmap("media/Yuna/basicAttack/basicAttackSprites.png");
        if (!p->spritePunch){
            fprintf(stderr, "Não foi possível carregar o sprite basicAttack\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 14; i++){
            p->xPicturePunch[i]  = 333*i;
        }
        p->actualPicturePunch = 0;
        p->totalFrame = 49;

        p->spriteKick = al_load_bitmap("media/Yuna/kick/kickSprites.png");
        if (!p->spriteKick){
            fprintf(stderr, "Não foi possível carregar o sprite kick\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 16; i++){
            p->xPictureKick[i] = 333*i;
        }
        p->actualPictureKick = 0;
        p->totalCooldown = 60;
        p->totalKick = 40;
    }
    return p;
}