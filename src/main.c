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

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_FONT* font = al_load_ttf_font("../media/Fonts/punk.ttf", 30, 0);
    ALLEGRO_FONT* round = al_load_ttf_font("../media/Fonts/punk.ttf", 40, 0);
    ALLEGRO_DISPLAY* disp = al_create_display(XSCREEN, YSCREEN);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Carregar imagem de fundo

    map* bMap = mapInit();
    battleMap (bMap, 1);
    
   
    player* player1 = playerInit(HANZO, 40, 260, 200, YSCREEN - 350, XSCREEN, YSCREEN - 10, 1); 
    if (!player1) return 1;
    
    player* player2 = playerInit(KIRA, 40, 260, XSCREEN - 200, YSCREEN - 350, XSCREEN, YSCREEN - 10, 2);
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

            //unsigned short punchReach = (player1->base / 2) + 220;
            //unsigned short kickReach = (player1->base / 2) + 220;

            /*if (player1->squat->isSquat && player2->squat->isSquat && !player1->jump->isJump && !player2->jump->isJump) {
                al_draw_filled_rectangle(player1->x - player1->base/2, player1->y, player1->x + player1->base/2, player1->y + player1->height/2, al_map_rgb(255, 0, 0));
    			al_draw_filled_rectangle(player2->x - player2->base/2, player2->y, player2->x + player2->base/2, player2->y + player2->height/2, al_map_rgb(0, 0, 255));
            }
			else if (player1->squat->isSquat && !player1->jump->isJump) {
                al_draw_filled_rectangle(player1->x - player1->base/2, player1->y, player1->x + player1->base/2, player1->y + player1->height/2, al_map_rgb(255, 0, 0));
    			al_draw_filled_rectangle(player2->x - player2->base/2, player2->y - player2->height/2, player2->x + player2->base/2, player2->y + player2->height/2, al_map_rgb(0, 0, 255));                
            }
            else if (player2->squat->isSquat && !player2->jump->isJump) {
                al_draw_filled_rectangle(player1->x - player1->base/2, player1->y - player1->height/2, player1->x + player1->base/2, player1->y + player1->height/2, al_map_rgb(255, 0, 0));
    			al_draw_filled_rectangle(player2->x - player2->base/2, player2->y, player2->x + player2->base/2, player2->y + player2->height/2, al_map_rgb(0, 0, 255));
            }
            else {
                al_draw_filled_rectangle(player1->x - player1->base/2, player1->y - player1->height/2, player1->x + player1->base/2, player1->y + player1->height/2, al_map_rgb(255, 0, 0));
			    al_draw_filled_rectangle(player2->x - player2->base/2, player2->y - player2->height/2, player2->x + player2->base/2, player2->y + player2->height/2, al_map_rgb(0, 0, 255));
            }*/
            
            /*
            // Player 1 punch walkBackward
            if (player1->fight->punch && player1->walkBackward) {
                if (!player1->squat->isSquat) {
                unsigned short punchX = player1->x - player1->base / 2;
                al_draw_filled_rectangle(punchX, player1->y - player1->height/2, punchX - punchReach, player1->y, al_map_rgb(255, 255, 255));
                } else {
                unsigned short punchX = player1->x - player1->base / 2;
                al_draw_filled_rectangle(punchX, player1->y + player1->height/2, punchX - punchReach, player1->y, al_map_rgb(255, 255, 255));    
                }
            //Player 1 punch walkForward
            } else if (player1->fight->punch && player1->walkForward) {
                if (!player1->squat->isSquat) {
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
                if (!player2->squat->isSquat) {
                unsigned short punchX = player2->x - player2->base / 2;
                al_draw_filled_rectangle(punchX, player2->y - player2->height/2, punchX - punchReach, player2->y, al_map_rgb(255, 255, 255));
                } else {
                unsigned short punchX = player2->x - player2->base / 2;
                al_draw_filled_rectangle(punchX, player2->y + player2->height/2, punchX - punchReach, player2->y, al_map_rgb(255, 255, 255));    
                }
            //Player 1 punch walkForward
            } else if (player2->fight->punch && player2->walkForward) {
                if (!player2->squat->isSquat) {
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
            }*/

            //Vida dos player 1
           
            al_draw_filled_rectangle(player1->healthStatus->xInit, player1->healthStatus->yInit, 
                player1->healthStatus->xEnd, player1->healthStatus->yEnd, player1->healthStatus->color);

            al_draw_bitmap(player1->healthStatus->picturePlayer, 100, 0, 0); 

            al_draw_filled_rectangle(player2->healthStatus->xInit, player2->healthStatus->yInit, 
                player2->healthStatus->xEnd, player2->healthStatus->yEnd, player2->healthStatus->color);
            
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
                    //proxRound();
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
                    //proxRound();
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
                    //proxRound();
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
                //timerOver
                reInitp1(player1);
                reInitp2(player2);
                //proxRound
                roundTimer = 60;
                actualRound ++;
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
            
            if (event.keyboard.keycode == ALLEGRO_KEY_Q && player1->fight->cooldown == 0 && !player1->fight->kick && !player1->dead->isDead) player1->fight->punch = 1;
            else if (event.keyboard.keycode == ALLEGRO_KEY_E && player1->fight->cooldown == 0 && !player1->fight->punch && !player1->dead->isDead) player1->fight->kick = 1;
            
            if (event.keyboard.keycode == 82) joystickLeft(player2->control);
            else if (event.keyboard.keycode == 83) joystickRight(player2->control);
            else if (event.keyboard.keycode == 85 && !player1->jump->isTop) joystickDown(player2->control);
        
            if (event.keyboard.keycode == 84) joystickUp(player2->control);
            
            if (event.keyboard.keycode == ALLEGRO_KEY_PAD_0 && player2->fight->cooldown == 0 && !player2->fight->kick && !player2->dead->isDead) player2->fight->punch = 1;
            else if (event.keyboard.keycode == ALLEGRO_KEY_PAD_1 && player2->fight->cooldown == 0 && !player2->fight->punch && !player2->dead->isDead) player2->fight->kick = 1;
        }
        else if (event.type == 42) break;
    }

    al_destroy_bitmap(bMap->background);
    //free(bMap);
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    //playerDestroy(player1);
    //playerDestroy(player2);
    al_destroy_display(disp);
    return 0;
}

