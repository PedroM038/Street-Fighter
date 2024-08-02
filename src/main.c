//comp: gcc stateMachine.c character.c fighter.c health.c screen.c joystick.c main.c -o shadowCombat -I/usr/include/x86_64-linux-gnu -lallegro_main -lallegro_font -lallegro_primitives -lallegro_image -lallegro

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "../include/fighter.h"
#include "../include/screen.h"
#include "../include/stateMachine.h"
#include "../include/character.h"
#include "../include/health.h"
#include "../include/joystick.h"

void drawVictory(unsigned char isVictory, ALLEGRO_DISPLAY* disp, ALLEGRO_FONT* round){
    if (!isVictory) return;
    else{
        ALLEGRO_EVENT_QUEUE* menuMapQueue = al_create_event_queue();
        ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
        ALLEGRO_EVENT event;

        al_register_event_source(menuMapQueue, al_get_keyboard_event_source());
        al_register_event_source(menuMapQueue, al_get_display_event_source(disp));
        al_register_event_source(menuMapQueue, al_get_timer_event_source(timer));

        unsigned char exitDV = 0;

        al_start_timer(timer);
        while (!exitDV){
            al_wait_for_event(menuMapQueue, &event);
            switch (event.type) {
                case ALLEGRO_EVENT_TIMER:
                    al_clear_to_color(al_map_rgb(0, 0, 0));

                    if (isVictory == 1) {
                        al_draw_text(round, al_map_rgb(255, 255, 0), 950, 400, ALLEGRO_ALIGN_CENTRE, "PLAYER 1 VICTORY");

                    } else if (isVictory == 2) {
                        al_draw_text(round, al_map_rgb(255, 255, 0), 950, 400, ALLEGRO_ALIGN_CENTRE, "PLAYER 2 VICTORY");
                    } else if (isVictory == 3){
                        al_draw_text(round, al_map_rgb(255, 255, 0), 950, 400, ALLEGRO_ALIGN_CENTRE, "A TIE");
                    }

                    al_draw_text(round, al_map_rgb(255, 255, 255), 950, 540, ALLEGRO_ALIGN_CENTRE, "PRESS ENTER");
                    al_flip_display();
                    break;

                case ALLEGRO_EVENT_KEY_DOWN:
                    switch (event.keyboard.keycode) {
                        case ALLEGRO_KEY_ENTER:
                            exitDV = 1;
                            break;
                    }
                    break;
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    exit(EXIT_SUCCESS);
            }
        }
    }
}

unsigned char updateVictory(player* player1, player* player2, unsigned char nRounds){
    if (player1->wins == 2){ //player1 venceu
        return 1;
    }
    else if (player2->wins == 2){ //player2 venceu
        return 2;
    }
    else if (nRounds > 3 && player1->wins < 2 && player2->wins < 2){ //empate
        return 3;
    }
    return 0;
}

void mapMenuChoice(menu* m, ALLEGRO_DISPLAY* disp){
    
    unsigned char controlChoice = 0;
    ALLEGRO_EVENT_QUEUE* menuMapQueue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT event;

    al_register_event_source(menuMapQueue, al_get_keyboard_event_source());
    al_register_event_source(menuMapQueue, al_get_display_event_source(disp));
    al_register_event_source(menuMapQueue, al_get_timer_event_source(timer));

    al_start_timer(timer);
     while (m->mapMenu->inMenuMap && controlChoice < 1) {
        al_wait_for_event(menuMapQueue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_scaled_bitmap(
                    m->menuBackground,
                    0, 0,
                    al_get_bitmap_width(m->menuBackground),
                    al_get_bitmap_height(m->menuBackground),
                    0, 0,
                    XSCREEN, YSCREEN, 0
                );

                al_draw_text(m->gameTitle, al_map_rgb(255, 255, 255), XSCREEN / 2, 100, ALLEGRO_ALIGN_CENTRE, "SHADOW COMBAT");

                if (m->mapMenu->actualChoice == 1) {
                    al_draw_bitmap(m->mapMenu->mapPicture1, 750, 350, 0);
                    al_draw_text(m->mapMenu->mapName, al_map_rgb(255, 255, 0), 950, 800, ALLEGRO_ALIGN_CENTRE, "Future Park");

                } else if (m->mapMenu->actualChoice == 2) {
                    al_draw_bitmap(m->mapMenu->mapPicture2, 750, 350, 0);
                    al_draw_text(m->mapMenu->mapName, al_map_rgb(255, 255, 0), 950, 800, ALLEGRO_ALIGN_CENTRE, "Sun Mountain");
                }
                al_flip_display();
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                    case ALLEGRO_KEY_RIGHT:
                        m->mapMenu->actualChoice = (m->mapMenu->actualChoice % 2) + 1;
                        break;
                    case ALLEGRO_KEY_ENTER:
                        if (m->mapMenu->actualChoice == 1){
                            if(controlChoice == 0){
                                m->gameChoice->mapChoice = 1;
                                controlChoice ++;
                                m->mapMenu->inMenuMap = 0;
                            }
                        }
                        else if (m->mapMenu->actualChoice == 2){
                            if(controlChoice == 0){
                                m->gameChoice->mapChoice = 2;
                                controlChoice ++;
                                m->mapMenu->inMenuMap = 0;
                            }
                        }
                        break;
                }
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                exit(EXIT_SUCCESS);
        }
    }
}

void characterMenu(menu* m, ALLEGRO_DISPLAY* disp){
    
    unsigned char controlChoice = 0;
    ALLEGRO_EVENT_QUEUE* menuCharacterQueue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT event;

    al_register_event_source(menuCharacterQueue, al_get_keyboard_event_source());
    al_register_event_source(menuCharacterQueue, al_get_display_event_source(disp));
    al_register_event_source(menuCharacterQueue, al_get_timer_event_source(timer));

    al_start_timer(timer);
     while (m->multiplayer->inMenuCharacter && controlChoice < 2) {
        al_wait_for_event(menuCharacterQueue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_scaled_bitmap(
                    m->menuBackground,
                    0, 0,
                    al_get_bitmap_width(m->menuBackground),
                    al_get_bitmap_height(m->menuBackground),
                    0, 0,
                    XSCREEN, YSCREEN, 0
                );

                al_draw_text(m->gameTitle, al_map_rgb(255, 255, 255), XSCREEN / 2, 100, ALLEGRO_ALIGN_CENTRE, "SHADOW COMBAT");
                if (controlChoice == 0) {
                    al_draw_text(m->multiplayer->playerNumber, al_map_rgb(0, 255, 0), 950, 300, ALLEGRO_ALIGN_CENTRE, "PLAYER 1"); 
                }
                else {
                     al_draw_text(m->multiplayer->playerNumber, al_map_rgb(255, 0, 0), 950, 300, ALLEGRO_ALIGN_CENTRE, "PLAYER 2");
                }
                if (m->multiplayer->actualChoice == KIRA) {
                    al_draw_text(m->multiplayer->characterName, al_map_rgb(255, 255, 0), 950, 850, ALLEGRO_ALIGN_CENTRE, "KIRA");
                    al_draw_scaled_bitmap(m->multiplayer->kiraPicture,
                        0, 0,
                        200, 180,
                        750, 350,
                        400, 500,
                        0
                    );
                } else if (m->multiplayer->actualChoice == HANZO) {
                    al_draw_text(m->multiplayer->characterName, al_map_rgb(255, 255, 0), 950, 850, ALLEGRO_ALIGN_CENTRE, "HANZO");
                    al_draw_scaled_bitmap(m->multiplayer->hanzoPicture,
                        0, 0,
                        200, 180,
                        750, 350,
                        400, 460,
                        0
                    );
                } else if (m->multiplayer->actualChoice == AIKO) {
                    al_draw_text(m->multiplayer->characterName, al_map_rgb(255, 255, 0), 950, 850, ALLEGRO_ALIGN_CENTRE, "AIKO");
                    al_draw_scaled_bitmap(m->multiplayer->aikoPicture,
                        0, 0,
                        200, 180,
                        750, 350,
                        400, 460,
                        0
                    );
                } else if (m->multiplayer->actualChoice == YUNA) {
                    al_draw_text(m->multiplayer->characterName, al_map_rgb(255, 255, 0), 950, 850, ALLEGRO_ALIGN_CENTRE, "YUNA");
                    al_draw_scaled_bitmap(m->multiplayer->yunaPicture,
                        0, 0,
                        200, 180,
                        750, 350,
                        400, 460,
                        0
                    );
                }
                al_flip_display();
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                        if (m->multiplayer->actualChoice == 1) {
                            m->multiplayer->actualChoice = 4; // Vai para o último personagem
                        } else {
                            m->multiplayer->actualChoice--; // Vai para o personagem anterior
                        }
                    break;
                    case ALLEGRO_KEY_RIGHT:
                        if (m->multiplayer->actualChoice == 4) {
                            m->multiplayer->actualChoice = 1; // Volta para o primeiro personagem
                        } else {
                            m->multiplayer->actualChoice++; // Vai para o próximo personagem
                        }
                    break;
                    case ALLEGRO_KEY_ENTER:
                        if (m->multiplayer->actualChoice == KIRA){
                            if(controlChoice == 0){
                                m->gameChoice->p1Choice = KIRA;
                                controlChoice ++;
                            }
                            else if (controlChoice == 1){
                                m->gameChoice->p2Choice = KIRA;
                                controlChoice ++;
                                m->multiplayer->inMenuCharacter = 0;
                            }
                        }
                        if (m->multiplayer->actualChoice == HANZO){
                            if(controlChoice == 0){
                                m->gameChoice->p1Choice = HANZO;
                                controlChoice ++;
                            }
                            else if (controlChoice == 1){
                                m->gameChoice->p2Choice = HANZO;
                                controlChoice ++;
                                m->multiplayer->inMenuCharacter = 0;
                            }
                        }
                        if (m->multiplayer->actualChoice == AIKO){
                            if(controlChoice == 0){
                                m->gameChoice->p1Choice = AIKO;
                                controlChoice ++;
                            }
                            else if (controlChoice == 1){
                                m->gameChoice->p2Choice = AIKO;
                                controlChoice ++;
                                m->multiplayer->inMenuCharacter = 0;
                            }
                        }
                        if (m->multiplayer->actualChoice == YUNA){
                            if(controlChoice == 0){
                                m->gameChoice->p1Choice = YUNA;
                                controlChoice ++;
                            }
                            else if (controlChoice == 1){
                                m->gameChoice->p2Choice = YUNA;
                                controlChoice ++;
                                m->multiplayer->inMenuCharacter = 0;
                            }
                        }
                        break;
                }
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                exit(EXIT_SUCCESS);
        }
    }
}

//retornar uma struct choice
void mainMenu(ALLEGRO_DISPLAY* disp, unsigned char* p1, unsigned char* p2, unsigned char* mapChoice) {
    menu* m = menuInit();
    ALLEGRO_EVENT_QUEUE* menuQueue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT event;

    al_register_event_source(menuQueue, al_get_keyboard_event_source());
    al_register_event_source(menuQueue, al_get_display_event_source(disp));
    al_register_event_source(menuQueue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    while (m->inMenuMain) {
        al_wait_for_event(menuQueue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_scaled_bitmap(
                    m->menuBackground,
                    0, 0,
                    al_get_bitmap_width(m->menuBackground),
                    al_get_bitmap_height(m->menuBackground),
                    0, 0,
                    XSCREEN, YSCREEN, 0
                );

                al_draw_text(m->gameTitle, al_map_rgb(255, 255, 255), XSCREEN / 2, 100, ALLEGRO_ALIGN_CENTRE, "SHADOW COMBAT");

                if (m->actualChoice == MULTIPLAYER) {
                    al_draw_text(m->fontMultiplayer, al_map_rgb(255, 255, 0), XSCREEN / 2, 700, ALLEGRO_ALIGN_CENTRE, "MULTIPLAYER");
                    al_draw_text(m->fontExit, al_map_rgb(255, 255, 255), XSCREEN / 2, 760, ALLEGRO_ALIGN_CENTRE, "EXIT");
                } else if (m->actualChoice == EXIT) {
                    al_draw_text(m->fontMultiplayer, al_map_rgb(255, 255, 255), XSCREEN / 2, 700, ALLEGRO_ALIGN_CENTRE, "MULTIPLAYER");
                    al_draw_text(m->fontExit, al_map_rgb(255, 255, 0), XSCREEN / 2, 760, ALLEGRO_ALIGN_CENTRE, "EXIT");
                }
                al_flip_display();
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_UP:
                    case ALLEGRO_KEY_DOWN:
                        m->actualChoice = (m->actualChoice % 2) + 1;
                        break;
                    case ALLEGRO_KEY_ENTER:
                        if (m->actualChoice == EXIT){
                            exit(EXIT_SUCCESS);
                        }
                        else if (m->actualChoice == MULTIPLAYER){
                            characterMenu(m, disp);
                            mapMenuChoice(m, disp);
                            m->inMenuMain = 0; //para teste
                        }
                        break;
                }
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                m->inMenuMain = 0;
                exit(EXIT_SUCCESS);
        }
    }

    *p1 = m->gameChoice->p1Choice;
    *p2 = m->gameChoice->p2Choice;
    *mapChoice = m->gameChoice->mapChoice;

    destroyMenu(m);
    al_destroy_event_queue(menuQueue);
    al_destroy_timer(timer);
}


int main (void) {
    if (!al_init()) {
        fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return -1;
    }
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_DISPLAY* disp = al_create_display(XSCREEN, YSCREEN);

    while (1){

        ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
        ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
        ALLEGRO_FONT* font = al_load_ttf_font("../media/Fonts/punk.ttf", 30, 0);
        ALLEGRO_FONT* round = al_load_ttf_font("../media/Fonts/punk.ttf", 40, 0);
        unsigned char p1Choice;
        unsigned char p2Choice;
        unsigned char mapChoice;
        
        mainMenu(disp, &p1Choice, &p2Choice, &mapChoice);
        
        al_register_event_source(queue, al_get_display_event_source(disp));
        al_register_event_source(queue, al_get_keyboard_event_source());
        al_register_event_source(queue, al_get_timer_event_source(timer));

        // Carregar imagem de fundo

        map* bMap = mapInit();
        battleMap (bMap, mapChoice);
        
    
        player* player1 = playerInit(p1Choice, 40, 260, 200, YSCREEN - 350, XSCREEN, YSCREEN - 10, 1); 
        if (!player1) return 1;
        
        player* player2 = playerInit(p2Choice, 40, 260, XSCREEN - 200, YSCREEN - 350, XSCREEN, YSCREEN - 10, 2);
        if (!player2) return 2;

        ALLEGRO_EVENT event;
        al_start_timer(timer);


        float player1_rect_width;
        float player1_rect_height;
        float player1_bitmap_width;
        float player1_bitmap_height;

        float player2_rect_width;
        float player2_rect_height;
        float player2_bitmap_width;
        float player2_bitmap_height;

        unsigned short roundTimer = 60;
        unsigned short timerControl = 1;
        unsigned char actualRound = 1;

        if (player1->hero == KIRA){
            player1_bitmap_width = 200;
            player1_bitmap_height = 159;
        
            player1_rect_width = player1->base * 14;
            player1_rect_height = player1->height * 1.85;
        } 
        else if (player1->hero == HANZO){
            player1_bitmap_width = 210;
            player1_bitmap_height = 180;
        
            player1_rect_width = player1->base * 13;
            player1_rect_height = player1->height * 1.95;
        }
        else if (player1->hero == AIKO){
            player1_bitmap_width = 269;
            player1_bitmap_height = 180;
        
            player1_rect_width = player1->base * 19;
            player1_rect_height = player1->height * 2.3;
        }
        else if (player1->hero == YUNA){
            player1_bitmap_width = 333;
            player1_bitmap_height = 190;
        
            player1_rect_width = player1->base * 22;
            player1_rect_height = player1->height * 1.88;
        }


        if (player2->hero == KIRA){
            player2_bitmap_width = 200;
            player2_bitmap_height = 159;
        
            player2_rect_width = player2->base * 14;
            player2_rect_height = player2->height * 1.85;
        } 
        else if (player2->hero == HANZO){
            player2_bitmap_width = 210;
            player2_bitmap_height = 180;
        
            player2_rect_width = player2->base * 13;
            player2_rect_height = player2->height * 1.95;
        }
        else if (player2->hero == AIKO){
            player2_bitmap_width = 269;
            player2_bitmap_height = 180;
        
            player2_rect_width = player2->base * 19;
            player2_rect_height = player2->height * 2.3;
        }
        else if (player2->hero == YUNA){
            player2_bitmap_width = 333;
            player2_bitmap_height = 190;
        
            player2_rect_width = player1->base * 22;
            player2_rect_height = player1->height * 1.88;
        }

        while(player1->wins < 2 && player2->wins < 2 && actualRound <= 3){
            al_wait_for_event(queue, &event);

            if (event.type == 30){
                updatePosition(player1, player2);
                al_clear_to_color(al_map_rgb(0, 0, 0));

                al_draw_scaled_bitmap(
                    bMap->background,
                    0, 0,
                    al_get_bitmap_width(bMap->background),
                    al_get_bitmap_height(bMap->background),
                    0,0,
                    XSCREEN,
                    YSCREEN,
                    0
                );

                timerControl++;
            
                al_draw_filled_rectangle(player1->healthStatus->xInit, player1->healthStatus->yInit, 
                    player1->healthStatus->xEnd, player1->healthStatus->yEnd, player1->healthStatus->color);
                
                al_draw_filled_rectangle(player1->staminaStatus->xInit, player1->staminaStatus->yInit,
                player1->staminaStatus->xEnd, player1->staminaStatus->yEnd, al_map_rgb(255,255,255));

                al_draw_filled_rectangle(player1->staminaStatus->xInit, player1->staminaStatus->yInit,
                player1->staminaStatus->xEnd, player1->staminaStatus->yEnd, al_map_rgb(255,255,255));

                al_draw_bitmap(player1->healthStatus->picturePlayer, 100, 0, 0); 

                al_draw_filled_rectangle(player2->healthStatus->xInit, player2->healthStatus->yInit, 
                    player2->healthStatus->xEnd, player2->healthStatus->yEnd, player2->healthStatus->color);
                
                al_draw_filled_rectangle(player2->staminaStatus->xInit, player2->staminaStatus->yInit,
                player2->staminaStatus->xEnd, player2->staminaStatus->yEnd, al_map_rgb(255,255,255));

                al_draw_bitmap(player2->healthStatus->picturePlayer, XSCREEN- 817, 0, 0); 

                if (player1->stop->isStop || player1->jump->isTop && !player1->dead->isDead) {
                    
                    unsigned char aPicture = player1->stop->actualPicture;

                    al_draw_scaled_bitmap(
                        player1->stop->sprite,
                        player1->stop->xPicture[aPicture], 0,
                        player1_bitmap_width, player1_bitmap_height,
                        player1->x - player1_rect_width /2, player1->y - player1_rect_height/2,
                        player1_rect_width, player1_rect_height,
                        0
                    );
                }

                if (player2->stop->isStop || player2->jump->isTop && !player2->dead->isDead) {

                    unsigned char aPicture = player2->stop->actualPicture;

                    al_draw_scaled_bitmap(
                        player2->stop->sprite,
                        player2->stop->xPicture[aPicture], 0,
                        player2_bitmap_width, player2_bitmap_height,
                        player2->x - player2_rect_width /2, player2->y - player2_rect_height/2,
                        player2_rect_width, player2_rect_height,
                        0
                    );
                }

                if (player1->walking->isWalking && !player1->jump->isJump && !player1->squat->isSquat && !player1->dead->isDead) {
            
                    unsigned char aPicture = player1->walking->actualPicture;
        
                    // Desenha o bitmap do personagem no retângulo do player 1
                    al_draw_scaled_bitmap(
                        player1->walking->sprite,
                        player1->walking->xPicture[aPicture], 0,
                        player1_bitmap_width, player1_bitmap_height,
                        player1->x - player1_rect_width / 2, player1->y - player1_rect_height/2,
                        player1_rect_width, player1_rect_height,
                        0
                    );
                }

                if (player2->walking->isWalking && !player2->jump->isJump && !player2->squat->isSquat && !player2->dead->isDead) {

                    unsigned char aPicture = player2->walking->actualPicture;
        
                    // Desenha o bitmap do personagem no retângulo do player 1
                    al_draw_scaled_bitmap(
                        player2->walking->sprite,
                        player2->walking->xPicture[aPicture], 0,
                        player2_bitmap_width, player2_bitmap_height,
                        player2->x - player2_rect_width / 2, player2->y - player2_rect_height/2,
                        player2_rect_width, player2_rect_height,
                        0
                    );
                }

                if (player1->jump->isJump && !player1->jump->isTop && !player1->dead->isDead) {
                    if (!player1->fight->punch && !player1->fight->kick){
                        unsigned char aPicture = player1->jump->actualPicture;
            
                        // Desenha o bitmap do personagem no retângulo do player 1
                        al_draw_scaled_bitmap(
                            player1->jump->sprite,
                            player1->walking->xPicture[aPicture], 0,
                            player1_bitmap_width, player1_bitmap_height,
                            player1->x - player1_rect_width / 2, player1->y - player1_rect_height/2,
                            player1_rect_width, player1_rect_height,
                            0
                        );
                    }
                }

                if (player2->jump->isJump && !player2->jump->isTop && !player2->dead->isDead) {
                    if (!player2->fight->punch && !player2->fight->kick){
                        unsigned char aPicture = player2->jump->actualPicture;
            
                        // Desenha o bitmap do personagem no retângulo do player 1
                        al_draw_scaled_bitmap(
                            player2->jump->sprite,
                            player2->walking->xPicture[aPicture], 0,
                            player2_bitmap_width, player2_bitmap_height,
                            player2->x - player2_rect_width / 2, player2->y - player2_rect_height/2,
                            player2_rect_width, player2_rect_height,
                            0
                        );
                    }
                }

                if (player1->squat->isSquat && !player1->jump->isTop && !player1->dead->isDead) {
                    if (!player1->fight->punch && !player1->fight->kick){
                        unsigned char aPicture = player1->squat->actualPicture;
            
                        // Desenha o bitmap do personagem no retângulo do player 1
                        al_draw_scaled_bitmap(
                            player1->squat->sprite,
                            player1->squat->xPicture[aPicture], 0,
                            player1_bitmap_width, player1_bitmap_height,
                            player1->x - player1_rect_width / 2, player1->y - player1_rect_height/2,
                            player1_rect_width, player1_rect_height,
                            0
                        );
                    }
                }

                if (player2->squat->isSquat && !player2->jump->isTop && !player2->dead->isDead) {
                    if (!player2->fight->punch && !player2->fight->kick){
                        unsigned char aPicture = player2->squat->actualPicture;
            
                        // Desenha o bitmap do personagem no retângulo do player 1
                        al_draw_scaled_bitmap(
                            player2->squat->sprite,
                            player2->squat->xPicture[aPicture], 0,
                            player2_bitmap_width, player2_bitmap_height,
                            player2->x - player2_rect_width / 2, player2->y - player2_rect_height/2,
                            player2_rect_width, player2_rect_height,
                            0
                        );
                    }
                }

                if (player1->fight->punch && !player1->fight->kick && !player1->dead->isDead) {
                    unsigned char aPicture = player1->fight->actualPicturePunch;
        
                    // Desenha o bitmap do personagem no retângulo do player 1
                    al_draw_scaled_bitmap(
                        player1->fight->spritePunch,
                        player1->fight->xPicturePunch[aPicture], 0,
                        player1_bitmap_width, player1_bitmap_height,
                        player1->x - player1_rect_width / 2, player1->y - player1_rect_height/2,
                        player1_rect_width, player1_rect_height,
                        0
                    );
                }

                if (player2->fight->punch && !player2->fight->kick && !player2->dead->isDead) {
                    unsigned char aPicture = player2->fight->actualPicturePunch;
        
                    // Desenha o bitmap do personagem no retângulo do player 1
                    al_draw_scaled_bitmap(
                        player2->fight->spritePunch,
                        player2->fight->xPicturePunch[aPicture], 0,
                        player2_bitmap_width, player2_bitmap_height,
                        player2->x - player2_rect_width / 2, player2->y - player2_rect_height/2,
                        player2_rect_width, player2_rect_height,
                        0
                    );
                }


                if (player1->fight->kick && !player1->fight->punch && !player1->dead->isDead) {
                    unsigned char aPicture = player1->fight->actualPictureKick;
        
                    // Desenha o bitmap do personagem no retângulo do player 1
                    al_draw_scaled_bitmap(
                        player1->fight->spriteKick,
                        player1->fight->xPictureKick[aPicture], 0,
                        player1_bitmap_width, player1_bitmap_height,
                        player1->x - player1_rect_width / 2, player1->y - player1_rect_height/2,
                        player1_rect_width, player1_rect_height,
                        0
                    );
                }

                if (player2->fight->kick && !player2->fight->punch && !player2->dead->isDead) {
                    unsigned char aPicture = player2->fight->actualPictureKick;
        
                    // Desenha o bitmap do personagem no retângulo do player 1
                    al_draw_scaled_bitmap(
                        player2->fight->spriteKick,
                        player2->fight->xPictureKick[aPicture], 0,
                        player2_bitmap_width, player2_bitmap_height,
                        player2->x - player2_rect_width / 2, player2->y - player2_rect_height/2,
                        player2_rect_width, player2_rect_height,
                        0
                    );
                }

                if(player1->dead->isDead && player2->dead->isDead){

                    unsigned char aPicture = player1->dead->actualPicture;
        
                    // Desenha o bitmap do personagem no retângulo do player 1
                    al_draw_scaled_bitmap(
                        player1->dead->sprite,
                        player1->dead->xPicture[aPicture], 0,
                        player1_bitmap_width, player1_bitmap_height,
                        player1->x - player1_rect_width / 2, player1->y - player1_rect_height/2,
                        player1_rect_width, player1_rect_height,
                        0
                    );
                    
                    aPicture = player2->dead->actualPicture;
        
                    // Desenha o bitmap do personagem no retângulo do player 1
                    al_draw_scaled_bitmap(
                        player2->dead->sprite,
                        player2->dead->xPicture[aPicture], 0,
                        player2_bitmap_width, player2_bitmap_height,
                        player2->x - player2_rect_width / 2, player2->y - player2_rect_height/2,
                        player2_rect_width, player2_rect_height,
                        0
                    );

                    if (player1->cooldown > 120 || player2->cooldown > 120){
                        player1->cooldown = 0;
                        player2->cooldown = 0;
                        player1->wins ++;
                        player2->wins ++;
                        reInitp1(player1);
                        reInitp2(player2);
                        roundTimer = 60;
                        actualRound ++;
                        unsigned char isVictory = updateVictory(player1, player2, actualRound);
                        drawVictory(isVictory, disp, round);
                        continue;
                    }
                    else{
                        player1->cooldown ++;
                        player2->cooldown ++;
                    }
                }
                else if(player1->dead->isDead){
                    
                    unsigned char aPicture = player1->dead->actualPicture;
        
                    // Desenha o bitmap do personagem no retângulo do player 1
                    al_draw_scaled_bitmap(
                        player1->dead->sprite,
                        player1->dead->xPicture[aPicture], 0,
                        player1_bitmap_width, player1_bitmap_height,
                        player1->x - player1_rect_width / 2, player1->y - player1_rect_height/2,
                        player1_rect_width, player1_rect_height,
                        0
                    );

                    if (player1->cooldown > 120){
                        player1->cooldown = 0;
                        player2->wins ++;
                        reInitp1(player1);
                        reInitp2(player2);
                        roundTimer = 60;
                        actualRound ++;
                        unsigned char isVictory = updateVictory(player1, player2, actualRound);
                        drawVictory(isVictory, disp, round);
                        continue;
                    }
                    else{
                        player1->cooldown ++;
                    }
                }
                else if(player2->dead->isDead){
                    
                    unsigned char aPicture = player2->dead->actualPicture;
        
                    // Desenha o bitmap do personagem no retângulo do player 1
                    al_draw_scaled_bitmap(
                        player2->dead->sprite,
                        player2->dead->xPicture[aPicture], 0,
                        player2_bitmap_width, player2_bitmap_height,
                        player2->x - player2_rect_width / 2, player2->y - player2_rect_height/2,
                        player2_rect_width, player2_rect_height,
                        0
                    );

                    if (player2->cooldown > 120){
                        player2->cooldown = 0;
                        player1->wins ++;
                        reInitp1(player1);
                        reInitp2(player2);
                        roundTimer = 60;
                        actualRound ++;
                        unsigned char isVictory = updateVictory(player1, player2, actualRound);
                        drawVictory(isVictory, disp, round);
                        continue;
                    }
                    else{
                        player2->cooldown ++;
                    }
                }

                if (timerControl > 59) {
                    timerControl = 1;
                    roundTimer --;
                }

                if (roundTimer == 0){

                    reInitp1(player1);
                    reInitp2(player2);
                    roundTimer = 60;
                    actualRound ++;

                    unsigned char isVictory = updateVictory(player1, player2, actualRound);
                    drawVictory(isVictory, disp, round);
                    continue;
                }

                al_draw_textf(round, al_map_rgb(255, 255, 255), XSCREEN / 2, 100, ALLEGRO_ALIGN_CENTRE, "Round %d", actualRound);
                al_draw_textf(font, al_map_rgb(255, 255, 255), XSCREEN / 2, 170, ALLEGRO_ALIGN_CENTRE, "%d", roundTimer);
                al_flip_display();
            }

            else if ((event.type == 10) || (event.type == 12)){
                if (event.keyboard.keycode == 1) joystickLeft(player1->control);
                else if (event.keyboard.keycode == 4) joystickRight(player1->control);
                else if (event.keyboard.keycode == 19 && !player2->jump->isTop) joystickDown(player1->control);

                if (event.keyboard.keycode == 23) joystickUp(player1->control);
                
                if (event.keyboard.keycode == ALLEGRO_KEY_Q && player1->fight->cooldown == 0 && !player1->fight->kick 
                    && !player1->dead->isDead && player1->staminaStatus->stamina > 100) player1->fight->punch = 1;

                else if (event.keyboard.keycode == ALLEGRO_KEY_E && player1->fight->cooldown == 0 && 
                !player1->fight->punch && !player1->dead->isDead && player1->staminaStatus->stamina > 150) player1->fight->kick = 1;
                
                if (event.keyboard.keycode == 82) joystickLeft(player2->control);
                else if (event.keyboard.keycode == 83) joystickRight(player2->control);
                else if (event.keyboard.keycode == 85 && !player1->jump->isTop) joystickDown(player2->control);
            
                if (event.keyboard.keycode == 84) joystickUp(player2->control);
                
                if (event.keyboard.keycode == ALLEGRO_KEY_PAD_0 && player2->fight->cooldown == 0 && !player2->fight->kick 
                    && !player2->dead->isDead && player2->staminaStatus->stamina > 100) player2->fight->punch = 1;
                else if (event.keyboard.keycode == ALLEGRO_KEY_PAD_1 && player2->fight->cooldown == 0 && 
                    !player2->fight->punch && !player2->dead->isDead && player2->staminaStatus->stamina > 150) player2->fight->kick = 1;
            }
            else if (event.type == 42) return 1;
        }
        playerDestroy(player1);
        playerDestroy(player2);
        al_destroy_bitmap(bMap->background);
        free (bMap);
        al_destroy_font(round);
        al_destroy_font(font);
        al_destroy_timer(timer);
        al_destroy_event_queue(queue);
    }
    al_destroy_display(disp);
    return 0;
}

