#include "../include/screen.h"

void battleMap(map* m, unsigned char choice) {
    if (choice == 1) {
        m->background = al_load_bitmap("../media/fundo1.jpg");
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