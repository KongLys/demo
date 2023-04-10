#include "enemies.h"
#include "bullet.h"
void movementEnemies(GameState* game)
{
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		if (game->enemies[i])
		{
			if (fabs(game->player.x - game->enemies[i]->x) > 200)
			{
				game->enemies[i]->x += game->enemies[i]->dx;
				game->enemies[i]->y += game->enemies[i]->dy;
				if (game->time % 100 == 0)
				{
					game->enemies[i]->dx *= -1;
					game->enemies[i]->dy *= -1;
					if (game->enemies[i]->dx > 0)
					{
						game->enemies[i]->flipChar = 1;
					}
					else
					{
						game->enemies[i]->flipChar = 0;
					}
				}
			}
			else
			{
				game->enemies[i]->x += 0;
				game->enemies[i]->y += 0;
				if (game->player.x < game->enemies[i]->x)
				{
					game->enemies[i]->flipChar = 0;
				}
				else
				{
					game->enemies[i]->flipChar = 1;
				}
				if (game->time % 10 == 0)
				{
					addBulletEnemies(game, i);
				}
			}
		}
	}
}

void movementEnemiesShort(GameState* game)
{
	for (int i = 0; i < NUM_ENEMIES_2; i++)
	{
		if (game->enemiesShort[i])
		{
			game->enemiesShort[i]->x += game->enemiesShort[i]->dx;
			game->enemiesShort[i]->y += game->enemiesShort[i]->dy;
			game->enemiesShort[i]->dy += GRAVITY;
			if (game->time % 100 == 0)
			{
				game->enemiesShort[i]->dx *= -1;
				if (game->enemiesShort[i]->dx > 0)
				{
					game->enemiesShort[i]->flipChar = 1;
				}
				else
				{
					game->enemiesShort[i]->flipChar = 0;
				}
			}
			else if (fabs(game->player.x - game->enemiesShort[i]->x) < 200 && game->player.x < game->enemiesShort[i]->x) //Left
			{
				game->enemiesShort[i]->dx = -4;
				game->enemiesShort[i]->flipChar = 0;

			}
			else if (fabs(game->player.x - game->enemiesShort[i]->x) < 200 && game->player.x > game->enemiesShort[i]->x) //Right
			{
				game->enemiesShort[i]->dx = 4;
				game->enemiesShort[i]->flipChar = 1;
			}
		}
	}
}

void aniEnemiesShort(GameState* game)
{
	for (int i = 0; i < NUM_ENEMIES_2; i++)
	{
		if (game->enemiesShort[i])
		{
			if (game->enemiesShort[i]->valid == 1 )
			{
				if (fabs(game->enemiesShort[i]->x - game->player.x) <= 150)
				{
					game->enemiesShort[i]->yAni = 2;
					if (game->time % 5 == 0)
					{
						game->enemiesShort[i]->xAni++;
						game->enemiesShort[i]->xAni %= 3;
					}
				}
				else
				{
					game->enemiesShort[i]->yAni = 1;
					if (game->time % 5 == 0)
					{
						game->enemiesShort[i]->xAni++;
						game->enemiesShort[i]->xAni %= 3;
					}
				}
			}
			else
			{
				game->enemiesShort[i]->yAni = 3;
				if (game->time % 5 == 0)
				{
					game->enemiesShort[i]->xAni++;
					if (game->enemiesShort[i]->xAni == 5)
					{
						removeEnemiesShort(game, i);
					}
				}
			}
		}
	}

}

void removeEnemies(GameState* game, int i)
{
	free(game->enemies[i]);
	game->enemies[i] = NULL;
}

void removeEnemiesShort(GameState* game, int i)
{
	free(game->enemiesShort[i]);
	game->enemiesShort[i] = NULL;
}