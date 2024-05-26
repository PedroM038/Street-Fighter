#include <stdio.h>
#include <stdlib.h>
#include "../include/square.h"

square* squareCreate(unsigned char side, unsigned short x, unsigned short y, unsigned short maxX, unsigned short maxY){

    if ((x - side/2 < 0) || (x + side/2 > maxX) || (y - side/2 < 0) || (y + side/2 > maxY)) return NULL;

    square *newSquare = (square*) malloc(sizeof(square));
    newSquare->side = side;
    newSquare->x = x;
    newSquare->y = y;
    return newSquare;
}

void squareMove(square* element, unsigned char steps, unsigned short trajectory, unsigned short maxX, unsigned short maxY){

    if (!trajectory){ //esquerda
        //Verifica se a movimentação para a esquerda é desejada e possível; se sim, efetiva a mesma
        if ((element->x - steps*SQUARE_STEP) - element->side/2 >= 0)
            element->x = element->x - steps*SQUARE_STEP;
    }

    else if (trajectory == 1){ //direita
        //Verifica se a movimentação para a direita é desejada e possível; se sim, efetiva a mesma
        if ((element->x + steps*SQUARE_STEP) + element->side/2 <= maxX) 
            element->x = element->x + steps*SQUARE_STEP;
    }

    else if (trajectory == 2){ //cima
        //Verifica se a movimentação para cima é desejada e possível; se sim, efetiva a mesma
        if ((element->y - steps*SQUARE_STEP) - element->side/2 >= 0) 
            element->y = element->y - steps*SQUARE_STEP;
    }

    else if (trajectory == 3){ //baixo
        //Verifica se a movimentação para baixo é desejada e possível; se sim, efetiva a mesma
        if ((element->y + steps*SQUARE_STEP) + element->side/2 <= maxY) 
            element->y = element->y + steps*SQUARE_STEP;
    }
}

void squareDestroy(square* element){
    free(element);
}
