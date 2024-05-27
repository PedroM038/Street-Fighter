#include <stdio.h>
#include <stdlib.h>
#include "../include/rectangle.h"

rectangle* rectangleCreate(unsigned char base, unsigned char height, unsigned short x, unsigned short y, unsigned short maxX, unsigned short maxY){

    if ((x - base/2 < 0) || (x + base/2 > maxX) || (y - height/2 < 0) || (y + height/2 > maxY)) return NULL;

    rectangle *newRectangle = (rectangle*) malloc(sizeof(rectangle));
    newRectangle->base = base;
    newRectangle->height = height;
    newRectangle->x = x;
    newRectangle->y = y;
    return newRectangle;
}

void rectangleMove(rectangle* element, unsigned char steps, unsigned short trajectory, unsigned short maxX, unsigned short maxY){

    if (!trajectory){ //esquerda
        //Verifica se a movimentação para a esquerda é desejada e possível; se sim, efetiva a mesma
        if ((element->x - steps*RECTANGLE_STEP) - element->base/2 >= 0)
            element->x = element->x - steps*RECTANGLE_STEP;
    }

    else if (trajectory == 1){ //direita
        //Verifica se a movimentação para a direita é desejada e possível; se sim, efetiva a mesma
        if ((element->x + steps*RECTANGLE_STEP) + element->base/2 <= maxX) 
            element->x = element->x + steps*RECTANGLE_STEP;
    }

    else if (trajectory == 2){ //cima
        //Verifica se a movimentação para cima é desejada e possível; se sim, efetiva a mesma
        if ((element->y - steps*RECTANGLE_STEP) - element->height/2 >= 0) 
            element->y = element->y - steps*RECTANGLE_STEP;
    }

    else if (trajectory == 3){ //baixo
        //Verifica se a movimentação para baixo é desejada e possível; se sim, efetiva a mesma
        if ((element->y + steps*RECTANGLE_STEP) + element->height/2 <= maxY) 
            element->y = element->y + steps*RECTANGLE_STEP;
    }
}

void rectangleDestroy(rectangle* element){
    free(element);
}
