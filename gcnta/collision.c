#include "main_func.h"


void collisionDetect(GameState* game)
{
	//Collision with bricks
	float px = game->player.x, py = game->player.y, pw = game->player.w, ph = game->player.h;
	for (int i = 0; i < NUM_PBRICK; i++)
	{
		//Player with bricks
		float bx = game->bricks[i].x, by = game->bricks[i].y, bw = game->bricks[i].w, bh = game->bricks[i].h;

		if (px + pw >= bx + 10 && px <= bx + bw - 10)
		{
			if (py + ph > by && py < by && game->player.dy > 0) //On brick
			{
				game->player.y = by - ph;
				py = by - ph;
				game->player.onBrick = 1;
				game->player.dy = 0;
			}
			if (py < by + bh && py > by && game->player.dy < 0) //Brick above
			{
				game->player.y = by + bh;
				py = by + bh;
				game->player.dy = 0;
			}
		}
		if (py + ph > by + 6 && py < by + bh * 39 / 40)
		{
			if (px + pw > bx && px < bx && game->player.dx > 0)
			{
				game->player.x = bx - pw; //edge left
				px = bx - pw;
				game->player.dx = 0;
			}
			else if (px < bx + bw && px + pw> bx + bw && game->player.dx < 0)
			{
				game->player.x = bx + bw; //edge right
				px = bx + bw;
				game->player.dx = 0;
			}
		}
		
		//collision enemies with bricks
		for (int j = 0; j < NUM_ENEMIES; j++)
		{
			if (game->enemies[j])
			{
				float ex = game->enemies[j]->x, ey = game->enemies[j]->y, ew = game->enemies[j]->w, eh = game->enemies[j]->h;
				if (ex + ew >= bx + 10 && ex <= bx + bw - 10)
				{
					if (ey + eh > by && ey < by && game->enemies[j]->dy > 0) //On brick
					{
						game->enemies[j]->y = by - eh;
						ey = by - eh;
					}
					if (ey < by + bh && ey > by && game->enemies[j]->dy < 0) //Brick above
					{
						game->enemies[j]->y = by + bh;
						ey = by + bh;
					}
				}
				if (ey + eh > by + 6 && ey < by + bh *39/40 )
				{

					if (ex + ew > bx && ex < bx && game->enemies[j]->dx > 0)
					{
						game->enemies[j]->x = bx - ew; //edge left
						ex = bx - ew;
					}
					else if (ex < bx + bw && ex + ew > bx + bw && game->enemies[j]->dx < 0)
					{
						game->enemies[j]->x = bx + bw; //edge right
						ex = bx + bw;
					}
				}
				
			}
		}
		for (int j = 0; j < NUM_ENEMIES_2; j++)
		{
			if (game->enemiesShort[j])
			{
				float esx = game->enemiesShort[j]->x, esy = game->enemiesShort[j]->y, esw = game->enemiesShort[j]->w, esh = game->enemiesShort[j]->h;
				if (esx + esw > bx -10 && esx < bx + bw + 10)
				{
					if (esy + esh > by && esy < by && game->enemiesShort[j]->dy > 0) //On brick
					{
						game->enemiesShort[j]->y = by - esh;
						esy = by - esh;
						game->enemiesShort[j]->dy = 0;
					}
				}
				if (esy + esh > by + 6 && esy < by + bh *39/40)
				{
					if (esx + esw > bx && esx < bx && game->enemiesShort[j]->dx > 0)
					{
						game->enemiesShort[j]->x = bx - esw; //edge left
						esx = bx - esw;
					}
					else if (esx < bx + bw && esx + esw> bx + bw && game->enemiesShort[j]->dx < 0)
					{
						game->enemiesShort[j]->x = bx + bw; //edge right
						esx = bx + bw;
					}
				}				
			}
		}
	}
}
short collisionPlayerWithEnnemies(GameState* game)
{
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		if (game->enemies[i])
		{
			if (game->player.x + game->player.w > game->enemies[i]->x && game->player.x < game->enemies[i]->x + game->enemies[i]->w && game->player.y + game->player.h > game->enemies[i]->y && game->player.y < game->enemies[i]->y + game->enemies[i]->h)
			{
				if(game->player.lives > 0)
				game->player.lives--;
				removeEnemies(game, i);
				return 1;
			}
		}
	}
	return 0;
}

short collisionPlayerWithEnnemiesShort(GameState* game)
{
	for (int i = 0; i < NUM_ENEMIES_2; i++)
	{
		if (game->enemiesShort[i] && game->enemiesShort[i]->valid == 1)
		{
			if (game->player.x + game->player.w > game->enemiesShort[i]->x && game->player.x < game->enemiesShort[i]->x + game->enemiesShort[i]->w && game->player.y + game->player.h > game->enemiesShort[i]->y && game->player.y < game->enemiesShort[i]->y + game->enemiesShort[i]->h)
			{
				if (game->player.lives > 0)
					game->player.lives--;
					removeEnemiesShort(game, i);
				return 1;
			}
		}
	}
	return 0;
}
