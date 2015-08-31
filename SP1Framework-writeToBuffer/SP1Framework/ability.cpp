#include "game.h"

extern CLASSES classes;
extern int iToken;
extern double elapsedTime; 
extern double uCooldown; // Ultimate skill cooldown
extern double t_tDamage; // Triple damage for warrior
extern double t_maxRange; // Ultimate skill for archer
extern double elapsedTime;
extern double uCooldown;
extern double t_dDamage;
extern double t_maxRange;
extern bool keyPressed[K_COUNT];

struct Stats {
    short health;
    short ammo;
    short bomb;
};
extern Stats player;

/* Classes
Done by Kwan Liang , 25 Aug 2015
Changes Gamestate to different states depending on which class is chosen
Changes player health and stats depending on class
*/

void Ultimate() {
    if (classes == BALANCED) {
        if (elapsedTime > uCooldown) {
            if (keyPressed[K_Q]) {
                uCooldown = elapsedTime + 60;
                player.health = 4;
            }
        }
    }
    if (classes == WARRIOR) {
        if (elapsedTime > uCooldown) {
            if (keyPressed[K_Q]) {
                uCooldown = elapsedTime + 60;
                if (iToken == 0){
                    iToken += 1;
                    t_dDamage = elapsedTime + 1;
                }
            }
        }
    }
    if (classes == ARCHER) {
        if (elapsedTime > uCooldown) {
            if (keyPressed[K_Q]) {
                uCooldown = elapsedTime + 60;
                t_maxRange = elapsedTime + 0.5;
            }
        }
    }
}