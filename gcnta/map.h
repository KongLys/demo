#pragma once
#include "libary.h"

#define MAX_X 200 //Number column of the map
#define MAX_Y 15 //Number row of the map

//val = 1 is wall
//val = 2 is enemies
//val = 3 is short enemies
//val = 4 is coin

int cntBrick(GameState* game);
int cntEnemies(GameState* game);
int cntEnemiesShort(GameState* game);
int cntCoin(GameState* game);

void loadEnemies(GameState* game);
void loadEnemiesShort(GameState* game);
void loadCoin(GameState* game);
void loadMap(GameState* game);