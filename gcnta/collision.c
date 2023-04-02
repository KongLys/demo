#include "Func.h"


void collisionDetect(GameState* game)
{
	//Collision with bricks
	for (int i = 0; i < NUM_PBRICK; i++)
	{
		float px = game->player.x, py = game->player.y, pw = game->player.w, ph = game->player.h;
		float bx = game->bricks[i].x, by = game->bricks[i].y, bw = game->bricks[i].w, bh = game->bricks[i].h;

		if (px + pw >= bx + 10 && px <= bx + bw - 10)
		{
			if (py + ph >= by && py < by && game->player.dy > 0) //On brick
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
		//collision bullet with bricks

		/*printf("x = %.2f\t", game->player.x);*/
		//printf("y = %.2f\n",game->player.y);
	}
}
short collision_with_ennemies(GameState* game)
{
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		if (game->enemies[i])
		{
			if (game->player.x + game->player.w > game->enemies[i]->x && game->player.x < game->enemies[i]->x + game->enemies[i]->w && game->player.y + game->player.h > game->enemies[i]->y && game->player.y < game->enemies[i]->y + game->enemies[i]->h)
			{
				return 1;
			}
		}
	}
	return 0;
}
