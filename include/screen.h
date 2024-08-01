#ifndef __SCREEN__
#define __SCREEN__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


#define XSCREEN 1920
#define YSCREEN 1080
#define MULTIPLAYER 1
#define EXIT 2

typedef struct choice{
    unsigned char p1Choice;
    unsigned char p2Choice;
    unsigned char mapChoice;
}choice;

typedef struct selectMap{

}selectMap;

typedef struct selectCharacter{
    unsigned char actualChoice;
    unsigned char inMenuCharacter;
    ALLEGRO_BITMAP* kiraPicture;
    ALLEGRO_BITMAP* hanzoPicture;
    ALLEGRO_FONT* characterName;
    ALLEGRO_FONT* playerNumber;
}selectCharacter;

typedef struct menu{
    ALLEGRO_BITMAP* menuBackground;
    ALLEGRO_FONT* gameTitle;
    ALLEGRO_FONT* fontMultiplayer;
    ALLEGRO_FONT* fontExit;
    unsigned char actualChoice;
    unsigned char inMenuMain;
    selectCharacter* multiplayer;
    selectMap* map;
    choice* gameChoice;
}menu;

typedef struct map{
    ALLEGRO_BITMAP* background;
    unsigned char choiceMap;
} map;

menu* menuInit();
void destroyMenu(menu* m);
void battleMap(map* m, unsigned char choice);
map* mapInit();

#endif