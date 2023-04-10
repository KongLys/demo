#include "bullet.h"

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
		game->bullets[found] = (Bullet*)malloc(sizeof(Bullet));
		game->bullets[found]->y = game->player.y + game->player.h / 2;
		if (game->player.flipChar == 0)
		{
			game->bullets[found]->dx = 20;
			game->bullets[found]->dy = 0;
			game->bullets[found]->x = game->player.x + game->player.w;
			game->bullets[found]->rangeLeft = game->bullets[found]->x - 500;
			game->bullets[found]->rangeRight = game->bullets[found]->x + 500;
		}
		else
		{
			game->bullets[found]->dx = -20;
			game->bullets[found]->dy = 0;
			game->bullets[found]->x = game->player.x;
			game->bullets[found]->rangeLeft = game->bullets[found]->x - 500;
			game->bullets[found]->rangeRight = game->bullets[found]->x + 500;
		}
	}
}


short checkBulletsWithBrick(GameState* game, int j)
{
	for (int i = 0; i < NUM_PBRICK; i++)
	{
		if (game->bullets[j]->x < game->bullets[j]->rangeLeft || game->bullets[j]->x > game->bullets[j]->rangeRight)
		{
			return 1;
		}
		if (game->bullets[j]->x + 8 > game->bricks[i].x && game->bullets[j]->x < game->bricks[i].x + game->bricks[i].w && game->bullets[j]->y + 8 > game->bricks[i].y && game->bullets[j]->y < game->bricks[i].y + game->bricks[i].h)
		{
			return 1;
		}
	}
	return 0;
}

short checkBulletsWithEnemies(GameState* game, int j)
{
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		if (game->enemies[i] != NULL)
		{
			if (game->bullets[j]->x + 8 >= game->enemies[i]->x && game->bullets[j]->x <= game->enemies[i]->x + game->enemies[i]->w && game->bullets[j]->y + 8 >= game->enemies[i]->y && game->bullets[j]->y <= game->enemies[i]->y + game->enemies[i]->h)
			{
				game->enemies[i]->lives--;
				if (game->enemies[i]->lives == 0)
				{
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
	for (int i = 0; i < NUM_ENEMIES_2; i++)
	{
		if (game->enemiesShort[i] != NULL)
		{
			if (game->bullets[j]->x + 8 >= game->enemiesShort[i]->x && game->bullets[j]->x <= game->enemiesShort[i]->x + game->enemiesShort[i]->w && game->bullets[j]->y + 8 >= game->enemiesShort[i]->y && game->bullets[j]->y <= game->enemiesShort[i]->y + game->enemiesShort[i]->h)
			{
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

short checkBullets(GameState* game, int j)
{
	if (checkBulletsWithBrick(game, j) == 1 || checkBulletsWithEnemies(game, j) == 1 || checkBulletsWithEnemiesShort(game, j) == 1)
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
	printf("%d\n",foundE);
	if (foundE >= 0)
	{
		game->bulletEnemies[foundE] = (Bullet*)malloc(sizeof(Bullet));
		game->bulletEnemies[foundE]->y = game->enemies[j]->y + game->enemies[j]->h / 2;
		if (game->enemies[j]->flipChar == 1) //When face to right
		{
			game->bulletEnemies[foundE]->dx = 20;
			game->bulletEnemies[foundE]->dy = 0;
			game->bulletEnemies[foundE]->x = game->enemies[j]->x + game->enemies[j]->w;
			game->bulletEnemies[foundE]->rangeLeft = game->bulletEnemies[foundE]->x - 400;
			game->bulletEnemies[foundE]->rangeRight = game->bulletEnemies[foundE]->x + 400;
		}
		else //When face to left
		{
			game->bulletEnemies[foundE]->dx = -20;
			game->bulletEnemies[foundE]->dy = 0;
			game->bulletEnemies[foundE]->x = game->enemies[j]->x;
			game->bulletEnemies[foundE]->rangeLeft = game->bulletEnemies[foundE]->x - 400;
			game->bulletEnemies[foundE]->rangeRight = game->bulletEnemies[foundE]->x + 400;
		}
	}
}

short checkBulletEnemiesWithBrick(GameState* game, int j, int k)
{
	for (int i = 0; i < NUM_PBRICK; i++)
	{
		if (game->bulletEnemies[j]->x < game->bulletEnemies[j]->rangeLeft || game->bulletEnemies[j]->x > game->bulletEnemies[j]->rangeRight)
		{
			return 1;
		}
		if (game->bulletEnemies[j]->x + 8 > game->bricks[i].x && game->bulletEnemies[j]->x < game->bricks[i].x + game->bricks[i].w && game->bulletEnemies[j]->y + 8 > game->bricks[i].y && game->bulletEnemies[j]->y < game->bricks[i].y + game->bricks[i].h)
		{
			return 1;
		}
	}
	return 0;
}

short checkBulletEnemies(GameState* game, int j, int k)
{
	if (checkBulletEnemiesWithBrick(game, j, k) == 1)
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
