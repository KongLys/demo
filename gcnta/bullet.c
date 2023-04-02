#include "Func.h"

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
	//printf("found %d \n", found);
	//fflush(stdout);
	if (found >= 0)
	{
		game->bullets[found] = (Bullet*)malloc(sizeof(Bullet));
		game->bullets[found]->y = game->player.y + game->player.h / 2;
		if (game->player.flipChar == 0)
		{
			game->bullets[found]->dx = 20;
			game->bullets[found]->x = game->player.x + game->player.w;
		}
		else
		{
			game->bullets[found]->dx = -20;
			game->bullets[found]->x = game->player.x;
		}
	}
}


short checkBulletsWithBrick(GameState* game, int j)
{
	for (int i = 0; i < NUM_PBRICK; i++)
	{
		if (game->bullets[j]->x < -game->bullets[j]->x - game->player.x - game->scrollX || game->bullets[j]->x > game->player.x - game->scrollX + 650)
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

short checkBullets(GameState* game, int j)
{
	if (checkBulletsWithBrick(game, j) == 1 || checkBulletsWithEnemies(game, j) == 1)
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