#pragma once
#include "libary.h"

//Bullet of player
void addBullet(GameState* game);

short checkBulletsWithBrick(GameState* game, int j);
short checkBulletsWithEnemies(GameState* game, int j);
short checkBulletsWithEnemiesShort(GameState* game, int j);
short checkBullets(GameState* game, int j);

void removeBullet(GameState* game, int i);



//bullet of enemies
void addBulletEnemies(GameState* game, int j);

short checkBulletEnemiesWithBrick(GameState* game, int j, int k);
short checkBulletEnemies(GameState* game, int j);

void removeBulletEnemies(GameState* game, int i);