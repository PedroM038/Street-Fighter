//mover o player quando estiver em cima do outro
//se ligar no tamanho dos vetores dos sprites
#ifndef __STATEMACHINE__
#define __STATEMACHINE__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_image.h>

#include "character.h"
#include "fighter.h"
#include "health.h"
#include "joystick.h"
#include "screen.h"

void playerMove(player* element, double steps, unsigned short trajectory, unsigned short maxX, unsigned short maxY);
unsigned char punchCollision(player* attacker, player* target);
void updatePunch(player* attacker, player* target);
unsigned char kickCollision(player* attacker, player* target);
void updateKick(player* attacker, player* target);
unsigned char collision(player* p1, player* p2);
void updateJump(player* playerJump, player* other);
void updatePosition(player* player1, player* player2);
void updateSquat(player* player1, player* player2);
void updateStop(player* p);
#endif