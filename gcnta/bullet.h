#pragma once
#include "libary.h"

void addBullet(GameState* game);
short checkBulletsWithBrick(GameState* game, int j);
short checkBulletsWithEnemies(GameState* game, int j);
short checkBullets(GameState* game, int j);
void removeBullet(GameState* game, int i);