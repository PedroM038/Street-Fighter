#include "../include/screen.h"

void destroyMenu(menu* m){
    if (!m) return;
    al_destroy_bitmap (m->menuBackground);
    al_destroy_font (m->gameTitle);
    al_destroy_font (m->fontMultiplayer);
    al_destroy_font (m->fontExit);
    free (m->gameChoice);
    //destroyMultiplayer();
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
    m->actualChoice = 1;
    m->inMenuMain = 1;
    m->multiplayer = characterInit();
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
    m->choiceMap = 0;
}