//comp: gcc rectangle.c joystick.c main.c -o rectangle -I/usr/include/x86_64-linux-gnu -lallegro_main -lallegro_font -lallegro_primitives -lallegro

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "../include/rectangle.h"

#define XSCREEN 1280
#define YSCREEN 720


unsigned char collision(rectangle* p1, rectangle* p2){
    if (p1->x + p1->base / 2 >= p2->x - p2->base / 2 &&  
        p1->x - p1->base / 2 <= p2->x + p2->base / 2 &&  
        p1->y + p1->height / 2 >= p2->y - p2->height / 2 &&  
        p1->y - p1->height / 2 <= p2->y + p2->height / 2) {  
            return 1;
    }
    return 0;
}

void updateJump(rectangle* playerJump, rectangle* other){
    if (playerJump->control->up && playerJump->jump == 0 && playerJump->y == playerJump->yInit) {
        playerJump->jump = 1;
        playerJump->velocityY = -40;
    }

    if (playerJump->jump) {
        playerJump->velocityY += playerJump->accelerationY;
        playerJump->y += playerJump->velocityY;

        if (collision(playerJump, other)) {
            playerJump->y -= playerJump->velocityY;
            playerJump->velocityY = 0; 
        }

        if (playerJump->y >= playerJump->yInit) {
            playerJump->y = playerJump->yInit;
            playerJump->jump = 0;
            playerJump->velocityY = 0;
        }
    }
}

void updatePosition(rectangle* player1, rectangle* player2){
    int prevX, prevY;

    prevX = player1->x;
    prevY = player1->y;
    if (player1->control->left) {
        rectangleMove(player1, 1, 0, XSCREEN, YSCREEN);
        if (collision(player1, player2)) { player1->x = prevX; player1->y = prevY; }
    }

    prevX = player1->x;
    prevY = player1->y;
    if (player1->control->right) {
        rectangleMove(player1, 1, 1, XSCREEN, YSCREEN);
        if (collision(player1, player2)) { player1->x = prevX; player1->y = prevY; }
    }

    updateJump(player1, player2);
    updatePunch(player1, player2);
    updateKick(player1, player2);

    prevX = player2->x;
    prevY = player2->y;
    if (player2->control->left) {
        rectangleMove(player2, 1, 0, XSCREEN, YSCREEN);
        if (collision(player1, player2)) { player2->x = prevX; player2->y = prevY; }
    }

    prevX = player2->x;
    prevY = player2->y;
    if (player2->control->right) {
        rectangleMove(player2, 1, 1, XSCREEN, YSCREEN);
        if (collision(player1, player2)) { player2->x = prevX; player2->y = prevY; }
    }
    updateJump(player2, player1);
    updatePunch(player2, player1);
    updateKick(player2, player1);
}


int main (void) {
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_DISPLAY* disp = al_create_display(1280, 720);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    rectangle* player1 = rectangleCreate(200, 240, 100, YSCREEN - 120, XSCREEN, YSCREEN); 
    if (!player1) return 1;
    
    rectangle* player2 = rectangleCreate(200, 240, XSCREEN - 100, YSCREEN - 120, XSCREEN, YSCREEN);
    if (!player2) return 2;


    ALLEGRO_EVENT event;
    al_start_timer(timer);

    while(1){
        al_wait_for_event(queue, &event);

        if (event.type == 30){
            updatePosition(player1, player2);
            al_clear_to_color(al_map_rgb(0, 0, 0));
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
            if (player1->fight->punch && player1->fight->walkBackward) {
                if (!player1->squat) {
                unsigned short punchX = player1->x - player1->base / 2;
                al_draw_filled_rectangle(punchX, player1->y - player1->height/2, punchX - punchReach, player1->y, al_map_rgb(255, 255, 255));
                } else {
                unsigned short punchX = player1->x - player1->base / 2;
                al_draw_filled_rectangle(punchX, player1->y + player1->height/2, punchX - punchReach, player1->y, al_map_rgb(255, 255, 255));    
                }
            //Player 1 punch walkForward
            } else if (player1->fight->punch && player1->fight->walkForward) {
                if (!player1->squat) {
                unsigned short punchX = player1->x + player1->base / 2;
                al_draw_filled_rectangle(punchX, player1->y - player1->height/2, punchX + punchReach, player1->y, al_map_rgb(255, 255, 255));
                } else {
                unsigned short punchX = player1->x + player1->base / 2;
                al_draw_filled_rectangle(punchX, player1->y + player1->height/2, punchX + punchReach, player1->y, al_map_rgb(255, 255, 255));    
                }
            }

            // Player 1 kick
            if (player1->fight->kick && player1->fight->walkForward) {
                unsigned short kickX = player1->x + player1->base / 2;
                al_draw_filled_rectangle(kickX, player1->y, kickX + kickReach, player1->y + player1->height / 2, al_map_rgb(255, 255, 255));
            } else if (player1->fight->kick && player1->fight->walkBackward) {
                unsigned short kickX = player1->x - player1->base / 2;
                al_draw_filled_rectangle(kickX, player1->y, kickX - kickReach, player1->y + player1->height / 2, al_map_rgb(255, 255, 255));
            }

            // Player 2 punch walkBackward
            if (player2->fight->punch && player2->fight->walkBackward) {
                if (!player2->squat) {
                unsigned short punchX = player2->x - player2->base / 2;
                al_draw_filled_rectangle(punchX, player2->y - player2->height/2, punchX - punchReach, player2->y, al_map_rgb(255, 255, 255));
                } else {
                unsigned short punchX = player2->x - player2->base / 2;
                al_draw_filled_rectangle(punchX, player2->y + player2->height/2, punchX - punchReach, player2->y, al_map_rgb(255, 255, 255));    
                }
            //Player 1 punch walkForward
            } else if (player2->fight->punch && player2->fight->walkForward) {
                if (!player2->squat) {
                unsigned short punchX = player2->x + player2->base / 2;
                al_draw_filled_rectangle(punchX, player2->y - player2->height/2, punchX + punchReach, player2->y, al_map_rgb(255, 255, 255));
                } else {
                unsigned short punchX = player2->x + player2->base / 2;
                al_draw_filled_rectangle(punchX, player2->y + player2->height/2, punchX + punchReach, player2->y, al_map_rgb(255, 255, 255));    
                }
            }

            // Player 2 kick
            if (player2->fight->kick && player2->fight->walkForward) {
                unsigned short kickX = player2->x + player2->base / 2;
                al_draw_filled_rectangle(kickX, player2->y, kickX + kickReach, player2->y + player2->height, al_map_rgb(255, 255, 255));
            } else if (player2->fight->kick && player2->fight->walkBackward) {
                unsigned short kickX = player2->x - player2->base / 2;
                al_draw_filled_rectangle(kickX, player2->y, kickX - kickReach, player2->y + player2->height, al_map_rgb(255, 255, 255));
            }
            
            if (player1->fight->collision) al_draw_text(font, al_map_rgb(255,0,0), XSCREEN/2 + 75, YSCREEN/2 - 20, 0, "PUNCH PLAYER 1 !");
            else if (player2->fight->collision) al_draw_text(font, al_map_rgb(0,0,255), XSCREEN/2 - 75, YSCREEN/2 - 20, 0, "PUNCH PLAYER 2 !");

            if (player1->fight->life <= 0 && player2->fight->life <= 0) break;
            else if (player1->fight->life <= 0) break;
            else if (player2->fight->life <= 0) break;
            
            al_flip_display();
        }

        else if ((event.type == 10) || (event.type == 12)){
            if (event.keyboard.keycode == 1){
                joystickLeft(player1->control);
            }
            else if (event.keyboard.keycode == 4){
                joystickRight(player1->control);
        
            }
            
            if (event.keyboard.keycode == 23) joystickUp(player1->control);
            else if (event.keyboard.keycode == 19) player1->squat = player1->squat ^ 1;

            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE && player1->fight->cooldown == 0) player1->fight->punch = 1;
            else if (event.keyboard.keycode == ALLEGRO_KEY_F && player1->fight->cooldown == 0) player1->fight->kick = 1;
            
            if (event.keyboard.keycode == 82) {
                joystickLeft(player2->control);
                player2->fight->walkBackward = 1;
                player2->fight->walkForward = 0;
            }
            else if (event.keyboard.keycode == 83) {
                joystickRight(player2->control);
                player2->fight->walkBackward = 0;
                player2->fight->walkForward = 1;
            }
            
            if (event.keyboard.keycode == 84) joystickUp(player2->control);
            else if (event.keyboard.keycode == 85) player2->squat = player2->squat ^ 1;

            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && player2->fight->cooldown == 0) player2->fight->punch = 1;
            else if (event.keyboard.keycode == ALLEGRO_KEY_PAD_2 && player2->fight->cooldown == 0) player2->fight->kick = 1;
        }
        else if (event.type == 42) break;
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    rectangleDestroy(player1);
    rectangleDestroy(player2);

    return 0;
}
