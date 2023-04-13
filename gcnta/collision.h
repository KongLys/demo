#pragma once
#include "libary.h"

void collisionDetect(GameState* game);
short collisionPlayerWithEnnemies(GameState* game);
short collisionPlayerWithEnnemiesShort(GameState* game);
short collisionPlayerWithBoss(GameState* game);

void collisionPlayerWithCoin(GameState* game);
short collisionPlayerWithCheckPoint(GameState* game);
short playerFall(GameState* game);