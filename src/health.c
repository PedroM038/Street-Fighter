#include "../include/health.h"

healthPlayer* healthInit(unsigned char hero, unsigned char player){

    healthPlayer* h = malloc(sizeof(healthPlayer));
    h->life = LIFE;
    h->color = al_map_rgb(0, 255, 0);
    
    h->yInit = 150;
    h->yEnd = h->yInit + 45;

    if (player == 1) {
        h->xInit = 100;
        h->xEnd = h->xInit + h->life;
    }
    else {
        h->xInit = XSCREEN - 100;
        h->xEnd = h->xInit - h->life;
    }

    if (hero == 1 && player == 1) h->picturePlayer = al_load_bitmap("media/Kira/pictureFrame/pictureLifeP1.png");
    
    else if (hero == 1 && player == 2) h->picturePlayer = al_load_bitmap("media/Kira/pictureFrame/pictureLifeP2.png");
    
    else if (hero == 2 && player == 1) h->picturePlayer = al_load_bitmap("media/Hanzo/pictureFrame/pictureLifeP1.png");
    
    else if (hero == 2 && player == 2) h->picturePlayer = al_load_bitmap("media/Hanzo/pictureFrame/pictureLifeP2.png");

    else if (hero == 3 && player == 1) h->picturePlayer = al_load_bitmap("media/Aiko/pictureFrame/pictureLifeP1.png");
    
    else if (hero == 3 && player == 2) h->picturePlayer = al_load_bitmap("media/Aiko/pictureFrame/pictureLifeP2.png");

    else if (hero == 4 && player == 1) h->picturePlayer = al_load_bitmap("media/Yuna/pictureFrame/pictureLifeP1.png");
    
    else if (hero == 4 && player == 2) h->picturePlayer = al_load_bitmap("media/Yuna/pictureFrame/pictureLifeP2.png");

    if (!h->picturePlayer){
        fprintf(stderr, "Não foi possível carregar o sprite health\n");
        exit(EXIT_FAILURE); 
    }

    return h;
}

void healthDestroy(healthPlayer* h);