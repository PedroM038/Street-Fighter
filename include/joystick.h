#ifndef __JOYSTICK__
#define __JOYSTICK__

typedef struct {
    unsigned char right;
    unsigned char left;
    unsigned char up;
    unsigned char down;
} joystick;

joystick* joystickCreate();
void joystickDestroy(joystick* element);
void joystickRight(joystick* element);
void joystickLeft(joystick* element);
void joystickUp(joystick* element);
void joystickDown(joystick* element);

#endif