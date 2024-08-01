#include <stdio.h>
#include <stdlib.h>
#include "../include/joystick.h"

joystick* joystickCreate(){

    joystick* element = (joystick*) malloc(sizeof(joystick));
    element->right = 0;
    element->left = 0;
    element->up = 0;
    element->down = 0;
    return element; 
}

void joystickDestroy(joystick* element){
    free(element);
}

void joystickLeft(joystick* element){
    element->left = element->left ^ 1;
}

void joystickRight(joystick* element){
    element->right = element->right ^ 1;
}

void joystickUp(joystick* element){
    element->up = element->up ^ 1;
}

void joystickDown(joystick* element){
    element->down = element->down ^ 1;
}


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