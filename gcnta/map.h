#pragma once
#include "libary.h"

#define MAX_X 400 //Number column of the map
#define MAX_Y 15 //Number row of the map

//val = 1 is wall
//val = 2 is enemies
//val = 3 is short enemies
//val = 4 is coin
//val = 5 is check point
//val = 6 is boss

int cntBrick(GameState* game);
int cntEnemies(GameState* game);
int cntEnemiesShort(GameState* game);
int cntBoss(GameState* game);
int cntCheckPoint(GameState* game);
int cntCoin(GameState* game);

void loadCheckPoint(GameState* game);
void loadEnemies(GameState* game);
void loadEnemiesShort(GameState* game);
void loadCoin(GameState* game);
void loadMap(GameState* game);