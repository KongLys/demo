#include "bullet.h"
#include "audio.h"

//Bullet of player
void addBullet(GameState* game)
{
	int found = -1;
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (game->bullets[i] == NULL)
		{
			found = i;
			break;
		}
	}
	if (found >= 0)
	{
		shotSound();
		game->bullets[found] = (Bullet*)malloc(sizeof(Bullet));
		game->bullets[found]->y = game->player.y + game->player.h / 2;
		if (game->player.flipChar == 0)
		{
			game->bullets[found]->dx = 20;
			game->bullets[found]->dy = 20 * sin(game->player.angle * M_PI / 180);
			game->bullets[found]->x = game->player.x + game->player.w;
			game->bullets[found]->rangeLeft = game->bullets[found]->x - 500;
			game->bullets[found]->rangeRight = game->bullets[found]->x + 500;
		}
		else
		{
			game->bullets[found]->dx = -20;
			game->bullets[found]->dy = 20 * sin(game->player.angle * M_PI / 180);
			game->bullets[found]->x = game->player.x;
			game->bullets[found]->rangeLeft = game->bullets[found]->x - 500;
			game->bullets[found]->rangeRight = game->bullets[found]->x + 500;
		}
	}
}


short checkBulletsWithBrick(GameState* game, int j)
{
	for (int i = 0; i < game->numBrick; i++)
	{
		if (game->bullets[j]->x < game->bullets[j]->rangeLeft || game->bullets[j]->x > game->bullets[j]->rangeRight)
		{
			return 1;
		}
		if (game->bullets[j]->x + 8 > game->bricks[i]->x && game->bullets[j]->x < game->bricks[i]->x + game->bricks[i]->w && game->bullets[j]->y + 8 > game->bricks[i]->y && game->bullets[j]->y < game->bricks[i]->y + game->bricks[i]->h)
		{
			return 1;
		}
	}
	return 0;
}

short checkBulletsWithEnemies(GameState* game, int j)
{
	for (int i = 0; i < game->numEnemies; i++)
	{
		if (game->enemies[i] != NULL)
		{
			if (game->bullets[j]->x + 8 >= game->enemies[i]->x && game->bullets[j]->x <= game->enemies[i]->x + game->enemies[i]->w && game->bullets[j]->y + 8 >= game->enemies[i]->y && game->bullets[j]->y <= game->enemies[i]->y + game->enemies[i]->h)
			{
				game->enemies[i]->lives--;
				if (game->enemies[i]->lives == 0)
				{
					game->player.score += 30;
					removeEnemies(game, i);
				}
				return 1;
			}
		}
	}
	return 0;
}

short checkBulletsWithEnemiesShort(GameState* game, int j)
{
	for (int i = 0; i < game->numEnemiesShort; i++)
	{
		if (game->enemiesShort[i] != NULL)
		{
			if (game->bullets[j]->x + 8 >= game->enemiesShort[i]->x && game->bullets[j]->x <= game->enemiesShort[i]->x + game->enemiesShort[i]->w && game->bullets[j]->y + 8 >= game->enemiesShort[i]->y && game->bullets[j]->y <= game->enemiesShort[i]->y + game->enemiesShort[i]->h)
			{
				if (game->enemiesShort[i]->valid)
				{
					game->player.score += 10;
				}
				if (game->enemiesShort[i]->lives > 0)
				{
					game->enemiesShort[i]->lives--;
				}
				if (game->enemiesShort[i]->lives == 0)
				{					
					game->enemiesShort[i]->valid = 0;
				}
				return 1;
			}
		}
	}
	return 0;
}

short checkBulletsWithBoss(GameState* game, int j)
{
	for (int i = 0; i < game->numBoss; i++)
	{
		if (game->boss[i] != NULL)
		{
			if (game->bullets[j]->x + 8 >= game->boss[i]->x + 90 && game->bullets[j]->x <= game->boss[i]->x + 180 && game->bullets[j]->y + 8 >= game->boss[i]->y +10 && game->bullets[j]->y <= game->boss[i]->y + 90)
			{
				game->boss[i]->lives--;
				if (game->boss[i]->lives == 0)
				{
					game->player.score += 999;
				}
				return 1;
			}
		}
	}
	return 0;
}

short checkBullets(GameState* game, int j)
{
	if (checkBulletsWithBrick(game, j) == 1 || checkBulletsWithEnemies(game, j) == 1 || checkBulletsWithEnemiesShort(game, j) == 1 || checkBulletsWithBoss(game, j) == 1)
	{
		return 1;
	}
	return 0;
}

void removeBullet(GameState* game, int i)
{
	if (game->bullets[i])
	{
		free(game->bullets[i]);
		game->bullets[i] = NULL;
	}
}


//Bullet of enemies
void addBulletEnemies(GameState* game, int j)
{
	int foundE = -1;
	for (int i = 0; i < MAX_BULLETS_ENEMIES; i++)
	{
		if (game->bulletEnemies[i] == NULL)
		{
			foundE = i;
			break;
		}
	}
	if (foundE >= 0)
	{
		game->bulletEnemies[foundE] = (Bullet*)malloc(sizeof(Bullet));
		game->bulletEnemies[foundE]->y = game->enemies[j]->y + game->enemies[j]->h / 2;
		if (game->enemies[j]->flipChar == 1) //When face to right
		{
			game->bulletEnemies[foundE]->dx = 10 * cos(atan2(game->player.y + game->player.h / 2 - game->enemies[j]->y - game->enemies[j]->h/2 , game->player.x + game->player.w / 2 - game->enemies[j]->x - game->enemies[j]->w ));
			game->bulletEnemies[foundE]->dy = 10 * sin(atan2(game->player.y + game->player.h / 2 - game->enemies[j]->y - game->enemies[j]->h/2 , game->player.x + game->player.w / 2 - game->enemies[j]->x - game->enemies[j]->w ));
			game->bulletEnemies[foundE]->x = game->enemies[j]->x + game->enemies[j]->w;
			game->bulletEnemies[foundE]->rangeLeft = game->bulletEnemies[foundE]->x - 400;
			game->bulletEnemies[foundE]->rangeRight = game->bulletEnemies[foundE]->x + 400;
		}
		else //When face to left
		{
			game->bulletEnemies[foundE]->dx = 10 * cos(atan2(game->player.y + game->player.h / 2 - game->enemies[j]->y - game->enemies[j]->h / 2, game->player.x + game->player.w / 2 - game->enemies[j]->x));
			game->bulletEnemies[foundE]->dy = 10 * sin(atan2(game->player.y + game->player.h / 2 - game->enemies[j]->y - game->enemies[j]->h / 2, game->player.x + game->player.w / 2 - game->enemies[j]->x));
			game->bulletEnemies[foundE]->x = game->enemies[j]->x;
			game->bulletEnemies[foundE]->rangeLeft = game->bulletEnemies[foundE]->x - 400;
			game->bulletEnemies[foundE]->rangeRight = game->bulletEnemies[foundE]->x + 400;
		}
	}
}

short checkBulletEnemiesWithBrick(GameState* game, int j)
{
	for (int i = 0; i < game->numBrick; i++)
	{
		if (game->bulletEnemies[j]->x < game->bulletEnemies[j]->rangeLeft || game->bulletEnemies[j]->x > game->bulletEnemies[j]->rangeRight)
		{
			return 1;
		}
		if (game->bulletEnemies[j]->x + 8 > game->bricks[i]->x && game->bulletEnemies[j]->x < game->bricks[i]->x + game->bricks[i]->w && game->bulletEnemies[j]->y + 8 > game->bricks[i]->y && game->bulletEnemies[j]->y < game->bricks[i]->y + game->bricks[i]->h)
		{
			return 1;
		}
	}
	return 0;
}

short checkBulletEnemiesWithPlayer(GameState* game, int j)
{
	if (game->bulletEnemies[j]->x + 8 >= game->player.x && game->bulletEnemies[j]->x <= game->player.x + game->player.w && game->bulletEnemies[j]->y + 8 >= game->player.y && game->bulletEnemies[j]->y <= game->player.y + game->player.h)
	{
		if (game->player.lives >= 0)
		{
			game->player.lives--;
			game->player.hit = 1;
		}
		return 1;
	}
	return 0;
}

short checkBulletEnemies(GameState* game, int j)
{
	if (checkBulletEnemiesWithBrick(game, j) == 1 || checkBulletEnemiesWithPlayer(game, j))
	{
		return 1;
	}
	return 0;
}

void removeBulletEnemies(GameState* game, int i)
{
	if (game->bulletEnemies[i])
	{
		free(game->bulletEnemies[i]);
		game->bulletEnemies[i] = NULL;
	}
}

//Boss
void addBulletBoss(GameState* game, int j)
{
	if (game->player.x >= game->bricks[1]->w * 360) {
		bossShot();
	}
	int foundB = -1;
	for (int i = 0; i < MAX_BULLETS_BOSS; i++)
	{
		if (game->bulletBoss[i] == NULL)
		{
			foundB = i;
			break;
		}
	}
	if (foundB >= 0)
	{
		game->bulletBoss[foundB] = (Bullet*)malloc(sizeof(Bullet));
		game->bulletBoss[foundB]->y = game->boss[j]->y + game->boss[j]->h / 2;
		game->bulletBoss[foundB]->x = game->boss[j]->x;
		game->bulletBoss[foundB]->dx = 10 * cos(atan2(game->player.y + game->player.h / 2 - game->boss[j]->y - game->boss[j]->h / 2, game->player.x + game->player.w / 2 - game->boss[j]->x));
		game->bulletBoss[foundB]->dy = 10 * sin(atan2(game->player.y + game->player.h / 2 - game->boss[j]->y - game->boss[j]->h / 2, game->player.x + game->player.w / 2 - game->boss[j]->x));
		game->bulletBoss[foundB]->rangeLeft = game->bulletBoss[foundB]->x - SCREEN_WIDTH;
		game->bulletBoss[foundB]->rangeRight = game->bulletBoss[foundB]->x + SCREEN_WIDTH;
	}
}

void ChangeOrbitBullet(GameState* game, int i)
{
	if (game->bulletBoss[i])
	{
		game->bulletBoss[i]->dx = 10 * sin(2 * game->time * 0.1 * M_PI / 180);
		game->bulletBoss[i]->dy = 10 * cos(2 * game->time * 0.1 * M_PI / 180);
	}
}

short checkBulletBossWithBrick(GameState* game, int j)
{
	for (int i = 0; i < game->numBrick; i++)
	{
		if (game->bulletBoss[j]->x < game->bulletBoss[j]->rangeLeft || game->bulletBoss[j]->x > game->bulletBoss[j]->rangeRight)
		{
			return 1;
		}
		if (game->bulletBoss[j]->x + 8 > game->bricks[i]->x && game->bulletBoss[j]->x < game->bricks[i]->x + game->bricks[i]->w && game->bulletBoss[j]->y + 8 > game->bricks[i]->y && game->bulletBoss[j]->y < game->bricks[i]->y + game->bricks[i]->h)
		{
			return 1;
		}
	}
	return 0;
}


short checkBulletBossWithPlayer(GameState* game, int j)
{
	if (game->bulletBoss[j]->x + 8 >= game->player.x && game->bulletBoss[j]->x <= game->player.x + game->player.w && game->bulletBoss[j]->y + 8 >= game->player.y && game->bulletBoss[j]->y <= game->player.y + game->player.h)
	{
		if (game->player.lives >= 0)
		{
			game->player.lives--;
			game->player.hit = 1;
		}
		return 1;
	}
	return 0;
}

short checkBulletBoss(GameState* game, int j)
{
	if (checkBulletBossWithBrick(game, j) == 1 || checkBulletBossWithPlayer(game, j))
	{
		return 1;
	}
	return 0;
}

void removeBulletBoss(GameState* game, int i)
{
	if (game->bulletBoss[i])
	{
		free(game->bulletBoss[i]);
		game->bulletBoss[i] = NULL;
	}
}