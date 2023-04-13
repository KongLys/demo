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

short checkBulletEnemiesWithBrick(GameState* game, int j);
short checkBulletEnemiesWithPlayer(GameState* game, int j);
short checkBulletEnemies(GameState* game, int j);

void removeBulletEnemies(GameState* game, int i);

//boss
void addBulletBoss(GameState* game, int j);

short checkBulletBossWithBrick(GameState* game, int j);
short checkBulletBossWithPlayer(GameState* game, int j);
short checkBulletsWithBoss(GameState* game, int j);

short checkBulletBoss(GameState* game, int j);

void removeBulletBoss(GameState* game, int i);