#include "../include/fighter.h"
#include <stdio.h>
#include <stdlib.h>

fight* punchInit(){
    fight* p = malloc(sizeof(fight));
    p->frame = 0;
    p->hit = 0;
    p->punch = 0;
    p->punchCooldown = 0;
    p->walkBackward = 0;
    p->walkForward = 0;
    return p;
}

void updatePunch(rectangle* attacker, rectangle* target) {
    if (attacker->attackPunch->punch) {
        // Verifica a colisão do soco
        if (punchCollision(attacker, target)) {
            printf("Punch hit!\n");
            // Aqui você pode adicionar lógica para reduzir a vida do adversário ou outros efeitos
        }

        // Atualiza o frame do soco
        attacker->attackPunch->frame++;
        if (attacker->attackPunch->frame > 10) {
            attacker->attackPunch->punch = 0;
            attacker->attackPunch->frame = 0;
            attacker->attackPunch->hit = 0;
            attacker->attackPunch->punchCooldown = 30;
        }
    } else if (attacker->attackPunch->punchCooldown > 0) {
        attacker->attackPunch->punchCooldown --;
    }
}

unsigned char punchCollision(rectangle* attacker, rectangle* target) {
    
    // Ajuste os valores conforme necessário para o alcance do soco
    unsigned short punchReach = (attacker->base / 2) + 10;

    if (attacker->attackPunch->punch) {
        if (attacker->control->right && 
            attacker->x + punchReach >= target->x - target->base / 2 &&
            attacker->x <= target->x + target->base / 2 &&
            attacker->y + attacker->height / 2 >= target->y - target->height / 2 &&
            attacker->y - attacker->height / 2 <= target->y + target->height / 2 &&
            attacker->attackPunch->hit == 0) {
            attacker->attackPunch->hit = 1;
            return 1;
        }

        if (attacker->control->left &&
            attacker->x - punchReach <= target->x + target->base / 2 &&
            attacker->x >= target->x - target->base / 2 &&
            attacker->y + attacker->height / 2 >= target->y - target->height / 2 &&
            attacker->y - attacker->height / 2 <= target->y + target->height / 2 &&
            attacker->attackPunch->hit == 0) {
            attacker->attackPunch->hit = 1;
            return 1;
        }
    }
    return 0;
}

void fightDestroy(rectangle* player){
    free(player->attackPunch);
}
