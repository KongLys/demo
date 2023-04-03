#include "enemies.h"

void movementEnemies(GameState* game)
{
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		if (game->enemies[i])
		{
			game->enemies[i]->x += game->enemies[i]->dx;
			if (game->time % 100 == 0)
			{
				game->enemies[i]->dx *= -1;
				if (game->enemies[i]->flipChar == 0)
				{
					game->enemies[i]->flipChar = 1;
				}
				else
				{
					game->enemies[i]->flipChar = 0;
				}
			}
			else if (fabs(game->player.x - game->enemies[i]->x) < 200 && game->player.x < game->enemies[i]->x) //Left
			{
				game->enemies[i]->dx = -4;
				game->enemies[i]->flipChar = 0;

			}
			else if (fabs(game->player.x - game->enemies[i]->x) < 200 && game->player.x > game->enemies[i]->x) //Right
			{
				game->enemies[i]->dx = 4;
				game->enemies[i]->flipChar = 1;

			}
		}
	}
}

void removeEnemies(GameState* game, int i)
{
	free(game->enemies[i]);
	game->enemies[i] = NULL;
}