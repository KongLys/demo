#pragma once

#include "libary.h"

void movementEnemiesShort(GameState* game);
void aniEnemiesShort(GameState* game);
void movementEnemies(GameState* game);
void bossShoot(GameState* game);

void removeEnemies(GameState* game, int i);
void removeEnemiesShort(GameState* game, int i);
void removeBoss(GameState* game, int i);