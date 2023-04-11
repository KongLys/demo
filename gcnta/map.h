#pragma once
#include "libary.h"

#define MAX_X 200 //Number column of the map
#define MAX_Y 15 //Number row of the map

int cntBrick(GameState* game);
int cntEnemies(GameState* game);
int cntEnemiesShort(GameState* game);

void loadEnemies(GameState* game);
void loadEnemiesShort(GameState* game);
void loadMap(GameState* game);