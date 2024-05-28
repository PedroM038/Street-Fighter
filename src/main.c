#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "../include/rectangle.h"

#define XSCREEN 1280
#define YSCREEN 720

void updatePosition(rectangle* player1, rectangle* player2){
    
    if (player1->control->left){
        rectangleMove(player1, 1, 0, XSCREEN, YSCREEN);
    }

    if (player1->control->right){
        rectangleMove(player1, 1, 1, XSCREEN, YSCREEN);
    }

    if (player1->control->up){
        rectangleMove(player1, 1, 2, XSCREEN, YSCREEN);
    }

    if (player1->control->down){
        rectangleMove(player1, 1, 3, XSCREEN, YSCREEN);
    }

    if (player2->control->left){
        rectangleMove(player2, 1, 0, XSCREEN, YSCREEN);
    }

    if (player2->control->right){
        rectangleMove(player2, 1, 1, XSCREEN, YSCREEN);
    }

    if (player2->control->up){
        rectangleMove(player2, 1, 2, XSCREEN, YSCREEN);
    }

    if (player2->control->down){
        rectangleMove(player2, 1, 3, XSCREEN, YSCREEN);
    }
}

int main (void) {
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_DISPLAY* disp = al_create_display(1280, 720);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    rectangle* player1 = rectangleCreate(108, 240, 54, YSCREEN - 120, XSCREEN, YSCREEN); 
    if (!player1) return 1;
    
    rectangle* player2 = rectangleCreate(108, 240, XSCREEN - 54, YSCREEN - 120, XSCREEN, YSCREEN);
    if (!player2) return 2;


    ALLEGRO_EVENT event;
    al_start_timer(timer);

    char flag = 0;

    while(1){
        al_wait_for_event(queue, &event);

        if (event.type == 30){
            updatePosition(player1, player2);
            al_clear_to_color(al_map_rgb(0, 0, 0));																																			
			al_draw_filled_rectangle(player1->x - player1->base/2, player1->y - player1->height/2, player1->x + player1->base/2, player1->y + player1->height/2, al_map_rgb(255, 0, 0));
			al_draw_filled_rectangle(player2->x - player2->base/2, player2->y - player2->height/2, player2->x + player2->base/2, player2->y + player2->height/2, al_map_rgb(0, 0, 255));
            al_flip_display();
        }

        else if ((event.type == 10) || (event.type == 12)){
            if (event.keyboard.keycode == 1) joystickLeft(player1->control);
            else if (event.keyboard.keycode == 4) joystickRight(player1->control);
            else if (event.keyboard.keycode == 23) joystickUp(player1->control);
            else if (event.keyboard.keycode == 19) joystickDown(player1->control);
            else if (event.keyboard.keycode == 82) joystickLeft(player2->control);
            else if (event.keyboard.keycode == 83) joystickRight(player2->control);
            else if (event.keyboard.keycode == 84) joystickUp(player2->control);
            else if (event.keyboard.keycode == 85) joystickDown(player2->control);
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
