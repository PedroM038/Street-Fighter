#include "../include/screen.h"

void destroyCharacterMenu(menu* m){
    if (!m->multiplayer) return;
    al_destroy_bitmap(m->multiplayer->hanzoPicture);
    al_destroy_bitmap(m->multiplayer->kiraPicture);
    al_destroy_font(m->multiplayer->characterName);
    al_destroy_font(m->multiplayer->playerNumber);
}

void destroyMapMenu(menu* m){
    if (!m->mapMenu) return;
    al_destroy_bitmap(m->mapMenu->mapPicture1);
    al_destroy_bitmap(m->mapMenu->mapPicture2);
    al_destroy_font(m->mapMenu->mapName);
}

void destroyMenu(menu* m){
    if (!m) return;
    al_destroy_bitmap (m->menuBackground);
    al_destroy_font (m->gameTitle);
    al_destroy_font (m->fontMultiplayer);
    al_destroy_font (m->fontExit);
    free (m->gameChoice);
    destroyCharacterMenu(m);
    free(m->multiplayer);
    destroyMapMenu(m);
    free(m->mapMenu);
    //destroySelectMap();
    free (m);
}

selectCharacter* characterInit(){
    selectCharacter* s = malloc (sizeof(selectCharacter));
    s->actualChoice = 1;
    s->inMenuCharacter = 1;
    s->characterName = al_load_ttf_font("../media/Fonts/punk.ttf", 40, 0);
    s->kiraPicture = al_load_bitmap("../media/Background/KiraPicture.png");
    s->hanzoPicture = al_load_bitmap("../media/Background/HanzoPicture.png");
    s->playerNumber = al_load_ttf_font("../media/Fonts/punk.ttf", 50, 0);
    return s;
}


selectMap* selectMapInit(){
    selectMap* m = malloc(sizeof(selectMap));
    m->actualChoice = 1;
    m->inMenuMap = 1;
    m->mapName = al_load_ttf_font("../media/Fonts/punk.ttf", 40, 0);
    m->mapPicture1 = al_load_bitmap("../media/Background/FutureParkPicture.jpg"); 
    m->mapPicture2 = al_load_bitmap("../media/Background/SunMountainPicture.jpg");
    return m;
}

menu* menuInit(){
    menu* m = malloc(sizeof(menu));
    if (!m){
        printf ("não foi possível alocar o Menu");
        exit(EXIT_FAILURE);
    }
    m->menuBackground = al_load_bitmap("../media/Background/menu.jpg");
    m->gameTitle = al_load_ttf_font("../media/Fonts/punk.ttf", 80, 0);
    m->fontMultiplayer = al_load_ttf_font("../media/Fonts/punk.ttf", 30, 0);
    m->fontExit = al_load_ttf_font("../media/Fonts/punk.ttf", 30, 0);
    m->gameChoice = malloc(sizeof(choice));
    m->gameChoice->mapChoice = 0;
    m->gameChoice->p1Choice = 0;
    m->gameChoice->p2Choice = 0;
    m->actualChoice = 1;
    m->inMenuMain = 1;
    m->multiplayer = characterInit();
    m->mapMenu = selectMapInit();
    return m;
}

void battleMap(map* m, unsigned char choice) {
    if (choice == 1) {
        m->background = al_load_bitmap("../media/Background/FuturePark.jpg");
        if (!m->background) {
            fprintf(stderr, "Falha ao carregar imagem de fundo.\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (choice == 2){
        m->background = al_load_bitmap("../media/Background/SunMountain.jpg");
        if (!m->background) {
            fprintf(stderr, "Falha ao carregar imagem de fundo.\n");
            exit(EXIT_FAILURE);
        }
    } 
}

map* mapInit(){
    map* m = malloc(sizeof(map));
    return m;
}