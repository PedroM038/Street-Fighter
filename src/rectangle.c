#include <stdio.h>
#include <stdlib.h>
#include "../include/rectangle.h"
#include "../include/joystick.h"

rectangle* rectangleCreate(unsigned char base, unsigned char height, unsigned short x, unsigned short y, unsigned short maxX, unsigned short maxY){
    if ((x - base/2 < 0) || (x + base/2 > maxX) || (y - height/2 < 0) || (y + height/2 > maxY)) return NULL;

    rectangle *newRectangle = (rectangle*) malloc(sizeof(rectangle));
    newRectangle->base = base;
    newRectangle->height = height;
    newRectangle->xInit = x;
    newRectangle->yInit = y;
    newRectangle->x = x;
    newRectangle->y = y;
    newRectangle->squat = 0;
    newRectangle->jump = 0;
    newRectangle->frame = 0;
    newRectangle->velocityY = 0;
    newRectangle->accelerationY = GRAVITY;
    newRectangle->control = joystickCreate();
    return newRectangle;
}

void rectangleMove(rectangle* element, double steps, unsigned short trajectory, unsigned short maxX, unsigned short maxY){

    if (!trajectory){ //esquerda
        if ((element->x - steps*RECTANGLE_STEP) - element->base/2 >= 0)
            element->x = element->x - steps*RECTANGLE_STEP;
    }

    else if (trajectory == 1){ //direita
        if ((element->x + steps*RECTANGLE_STEP) + element->base/2 <= maxX) 
            element->x = element->x + steps*RECTANGLE_STEP;
    }

    else if (trajectory == 2){ //cima
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
    joystickDestroy(element->control);
    free(element);
}
