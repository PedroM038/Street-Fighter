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