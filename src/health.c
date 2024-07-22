#include "../include/health.h"

healthPlayer* healthInit(unsigned char hero, unsigned char player){

    healthPlayer* h = malloc(sizeof(healthPlayer));
    h->life = LIFE;
    h->color = al_map_rgb(0, 255, 0);
    
    h->yInit = 100;
    h->yEnd = h->yInit + 30;

    if (player == 1) {
        h->xInit = 200;
        h->xEnd = h->xInit + h->life;
    }
    else {
        h->xInit = XSCREEN - h->life - 200;
        h->xEnd = h->xInit + h->life;
    }

    /*if (hero == KIRA) h->picturePlayer = al_load_bitmap("../media/Kira/picture/healthPicture.png");
    else if (hero == HANZO) h->picturePlayer = al_load_bitmap("../media/Hanzo/picture/healthPicture.png");
    if (!h->picturePlayer){
        fprintf(stderr, "Não foi possível carregar o sprite health\n");
        exit(EXIT_FAILURE); 
    }*/
}

void healthDestroy(healthPlayer* h);