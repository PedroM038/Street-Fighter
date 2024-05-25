#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

int main (void) {
    al_init();
    al_install_keyboard();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_DISPLAY* disp = al_create_display(1280, 720);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT event;
    al_start_timer(timer);

    char flag = 0;

    while(1){
        al_wait_for_event(queue, &event);

        if (event.type == 30){
            if (flag <= 15) {
                al_clear_to_color(al_map_rgb(0,0,0));
                flag++;
            }
            else {
                al_clear_to_color(al_map_rgb(255,255,255));
                flag++;
                if (!(flag % 15)) flag = 0;
            }

            al_flip_display();
        }

        else if (event.type == 42) break;
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
