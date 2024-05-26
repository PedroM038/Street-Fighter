#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "../include/square.h"

#define XSCREEN 1280
#define YSCREEN 720

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

    square* player1 = squareCreate (100, 50, YSCREEN - 50, XSCREEN, YSCREEN);
    if (!player1) return 1;
    
    square* player2 = squareCreate (100, XSCREEN - 50, YSCREEN - 50, XSCREEN, YSCREEN);
    if (!player2) return 2;


    ALLEGRO_EVENT event;
    al_start_timer(timer);

    char flag = 0;

    while(1){
        al_wait_for_event(queue, &event);

        if (event.type == 30){
            al_clear_to_color(al_map_rgb(0, 0, 0));																																			
			al_draw_filled_rectangle(player1->x - player1->side/2, player1->y - player1->side/2, player1->x + player1->side/2, player1->y + player1->side/2, al_map_rgb(255, 0, 0));
			al_draw_filled_rectangle(player2->x - player2->side/2, player2->y - player2->side/2, player2->x + player2->side/2, player2->y + player2->side/2, al_map_rgb(0, 0, 255));
            al_flip_display();
        }

        else if (event.type == 42) break;
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    squareDestroy(player1);
    squareDestroy(player2);

    return 0;
}
