//comp: gcc stateMachine.c character.c fighter.c health.c screen.c joystick.c main.c -o shadowCombat -I/usr/include/x86_64-linux-gnu -lallegro_main -lallegro_font -lallegro_primitives -lallegro_image -lallegro

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "../include/fighter.h"
#include "../include/screen.h"
#include "../include/stateMachine.h"
#include "../include/character.h"
#include "../include/health.h"
#include "../include/joystick.h"

int main (void) {
    if (!al_init()) {
        fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return -1;
    }
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();  // Inicializa o add-on de imagens


    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_DISPLAY* disp = al_create_display(1280, 720);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Carregar imagem de fundo

    /*map* bMap = mapInit();
    battleMap (bMap, 1);
    */
   
    player* player1 = playerInit(KIRA, 240, 260, 200, YSCREEN - 240, XSCREEN, YSCREEN); 
    if (!player1) return 1;
    
    player* player2 = playerInit(HANZO, 240, 260, XSCREEN - 200, YSCREEN - 240, XSCREEN, YSCREEN);
    if (!player2) return 2;

    ALLEGRO_EVENT event;
    al_start_timer(timer);

    while(1){
        al_wait_for_event(queue, &event);

        if (event.type == 30){
            updatePosition(player1, player2);
            al_clear_to_color(al_map_rgb(0, 0, 0));

        /*al_draw_scaled_bitmap(
            bMap->background,
            0, 0,
            al_get_bitmap_width(bMap->background),
            al_get_bitmap_height(bMap->background),
            0,0,
            XSCREEN,
            YSCREEN,
            0
        );*/

            if (player1->squat && player2->squat && !player1->jump && !player2->jump) {
                al_draw_filled_rectangle(player1->x - player1->base/2, player1->y, player1->x + player1->base/2, player1->y + player1->height/2, al_map_rgb(255, 0, 0));
    			al_draw_filled_rectangle(player2->x - player2->base/2, player2->y, player2->x + player2->base/2, player2->y + player2->height/2, al_map_rgb(0, 0, 255));
            }
			else if (player1->squat && !player1->jump) {
                al_draw_filled_rectangle(player1->x - player1->base/2, player1->y, player1->x + player1->base/2, player1->y + player1->height/2, al_map_rgb(255, 0, 0));
    			al_draw_filled_rectangle(player2->x - player2->base/2, player2->y - player2->height/2, player2->x + player2->base/2, player2->y + player2->height/2, al_map_rgb(0, 0, 255));                
            }
            else if (player2->squat && !player2->jump) {
                al_draw_filled_rectangle(player1->x - player1->base/2, player1->y - player1->height/2, player1->x + player1->base/2, player1->y + player1->height/2, al_map_rgb(255, 0, 0));
    			al_draw_filled_rectangle(player2->x - player2->base/2, player2->y, player2->x + player2->base/2, player2->y + player2->height/2, al_map_rgb(0, 0, 255));
            }
            else {
                al_draw_filled_rectangle(player1->x - player1->base/2, player1->y - player1->height/2, player1->x + player1->base/2, player1->y + player1->height/2, al_map_rgb(255, 0, 0));
			    al_draw_filled_rectangle(player2->x - player2->base/2, player2->y - player2->height/2, player2->x + player2->base/2, player2->y + player2->height/2, al_map_rgb(0, 0, 255));
            }
            unsigned short punchReach = (player1->base / 2) + 40;
            unsigned short kickReach = (player1->base / 2) + 70;

            // Player 1 punch walkBackward
            if (player1->fight->punch && player1->walkBackward) {
                if (!player1->squat) {
                unsigned short punchX = player1->x - player1->base / 2;
                al_draw_filled_rectangle(punchX, player1->y - player1->height/2, punchX - punchReach, player1->y, al_map_rgb(255, 255, 255));
                } else {
                unsigned short punchX = player1->x - player1->base / 2;
                al_draw_filled_rectangle(punchX, player1->y + player1->height/2, punchX - punchReach, player1->y, al_map_rgb(255, 255, 255));    
                }
            //Player 1 punch walkForward
            } else if (player1->fight->punch && player1->walkForward) {
                if (!player1->squat) {
                unsigned short punchX = player1->x + player1->base / 2;
                al_draw_filled_rectangle(punchX, player1->y - player1->height/2, punchX + punchReach, player1->y, al_map_rgb(255, 255, 255));
                } else {
                unsigned short punchX = player1->x + player1->base / 2;
                al_draw_filled_rectangle(punchX, player1->y + player1->height/2, punchX + punchReach, player1->y, al_map_rgb(255, 255, 255));    
                }
            }

            // Player 1 kick
            if (player1->fight->kick && player1->walkForward) {
                unsigned short kickX = player1->x + player1->base / 2;
                al_draw_filled_rectangle(kickX, player1->y, kickX + kickReach, player1->y + player1->height / 2, al_map_rgb(255, 255, 255));
            } else if (player1->fight->kick && player1->walkBackward) {
                unsigned short kickX = player1->x - player1->base / 2;
                al_draw_filled_rectangle(kickX, player1->y, kickX - kickReach, player1->y + player1->height / 2, al_map_rgb(255, 255, 255));
            }

            // Player 2 punch walkBackward
            if (player2->fight->punch && player2->walkBackward) {
                if (!player2->squat) {
                unsigned short punchX = player2->x - player2->base / 2;
                al_draw_filled_rectangle(punchX, player2->y - player2->height/2, punchX - punchReach, player2->y, al_map_rgb(255, 255, 255));
                } else {
                unsigned short punchX = player2->x - player2->base / 2;
                al_draw_filled_rectangle(punchX, player2->y + player2->height/2, punchX - punchReach, player2->y, al_map_rgb(255, 255, 255));    
                }
            //Player 1 punch walkForward
            } else if (player2->fight->punch && player2->walkForward) {
                if (!player2->squat) {
                unsigned short punchX = player2->x + player2->base / 2;
                al_draw_filled_rectangle(punchX, player2->y - player2->height/2, punchX + punchReach, player2->y, al_map_rgb(255, 255, 255));
                } else {
                unsigned short punchX = player2->x + player2->base / 2;
                al_draw_filled_rectangle(punchX, player2->y + player2->height/2, punchX + punchReach, player2->y, al_map_rgb(255, 255, 255));    
                }
            }

            // Player 2 kick
            if (player2->fight->kick && player2->walkForward) {
                unsigned short kickX = player2->x + player2->base / 2;
                al_draw_filled_rectangle(kickX, player2->y, kickX + kickReach, player2->y + player2->height, al_map_rgb(255, 255, 255));
            } else if (player2->fight->kick && player2->walkBackward) {
                unsigned short kickX = player2->x - player2->base / 2;
                al_draw_filled_rectangle(kickX, player2->y, kickX - kickReach, player2->y + player2->height, al_map_rgb(255, 255, 255));
            }
            
            if (player1->fight->collision) al_draw_text(font, al_map_rgb(255,0,0), XSCREEN/2 + 75, YSCREEN/2 - 20, 0, "PUNCH PLAYER 1 !");
            else if (player2->fight->collision) al_draw_text(font, al_map_rgb(0,0,255), XSCREEN/2 - 75, YSCREEN/2 - 20, 0, "PUNCH PLAYER 2 !");

            if (player1->fight->life <= 0 && player2->fight->life <= 0) break;
            else if (player1->fight->life <= 0) break;
            else if (player2->fight->life <= 0) break;
            
            if (player1->stop->isStop) {
                // Calcula a largura e a altura do bitmap do personagem
                float player_bitmap_width = al_get_bitmap_width(player1->stop->picture);
                float player_bitmap_height = al_get_bitmap_height(player1->stop->picture);
    
                // Calcula a largura e a altura do retângulo do player 1
                float player_rect_width = player1->base * 1.2;
                float player_rect_height = player1->height * 1.2;
    
                // Desenha o bitmap do personagem no retângulo do player 1
                al_draw_scaled_bitmap(
                    player1->stop->picture,
                    0, 0,
                    player_bitmap_width, player_bitmap_height,
                    player1->x - player_rect_width /2, player1->y - player_rect_height/2,
                    player_rect_width, player_rect_height,
                    0
                );
            }
            if (player1->walking->isWalking) {
                // Calcula a largura e a altura do bitmap do personagem
                float player_bitmap_width = al_get_bitmap_width(player1->walking->picture);
                float player_bitmap_height = al_get_bitmap_height(player1->walking->picture);
    
                // Calcula a largura e a altura do retângulo do player 1
                float player_rect_width = player1->base * 1.2;
                float player_rect_height = player1->height * 1.2;
    
                // Desenha o bitmap do personagem no retângulo do player 1
                al_draw_scaled_bitmap(
                    player1->walking->picture,
                    0, 0,
                    player_bitmap_width, player_bitmap_height,
                    player1->x - player_rect_width / 2, player1->y - player_rect_height/2,
                    player_rect_width, player_rect_height,
                    0
                );
            }
            al_flip_display();
        }

        else if ((event.type == 10) || (event.type == 12)){
            if (event.keyboard.keycode == 1){
                joystickLeft(player1->control);
            }
            else if (event.keyboard.keycode == 4) joystickRight(player1->control);
            
            if (event.keyboard.keycode == 23) joystickUp(player1->control);
            else if (event.keyboard.keycode == 19 && !player2->isTop) player1->squat = player1->squat ^ 1;

            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE && player1->fight->cooldown == 0) player1->fight->punch = 1;
            else if (event.keyboard.keycode == ALLEGRO_KEY_F && player1->fight->cooldown == 0) player1->fight->kick = 1;
            
            if (event.keyboard.keycode == 82) joystickLeft(player2->control);
            else if (event.keyboard.keycode == 83) joystickRight(player2->control);
            
            if (event.keyboard.keycode == 84) joystickUp(player2->control);
            else if (event.keyboard.keycode == 85 && !player1->isTop) player2->squat = player2->squat ^ 1;

            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && player2->fight->cooldown == 0) player2->fight->punch = 1;
            else if (event.keyboard.keycode == ALLEGRO_KEY_PAD_2 && player2->fight->cooldown == 0) player2->fight->kick = 1;
        }
        else if (event.type == 42) break;
    }

    //al_destroy_bitmap(bMap->background);
    //free(bMap);
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    //playerDestroy(player1);
    //playerDestroy(player2);
    al_destroy_display(disp);
    return 0;
}

