﻿#include "screen_status.h"

void initStatusLives(GameState* game)
{
	if (game->player.lives > 0)
	{
		char* str = (char*)malloc(10, sizeof(char));
		sprintf_s(str, 10, "x %d", game->player.lives);

		SDL_Color white = { 255, 255, 255, 255 };
		SDL_Surface* tmp = TTF_RenderText_Blended(game->font, str, white);
		game->label_h = 50;
		game->label_w = 100;
		game->label = SDL_CreateTextureFromSurface(game->renderer1, tmp);
		SDL_FreeSurface(tmp);
		free(str);
	}
	else
	{
		char* str = (char*)malloc(10, sizeof(char));
		sprintf_s(str, 10, "x %d", 3 - game->player.lives);

		SDL_Color white = { 255, 255, 255, 255 };
		SDL_Surface* tmp = TTF_RenderText_Blended(game->font, str, white);
		game->label_h = 50;
		game->label_w = 100;
		game->label = SDL_CreateTextureFromSurface(game->renderer1, tmp);
		SDL_FreeSurface(tmp);
		free(str);
	}
}

void screenStart(SDL_Renderer* renderer, GameState* game)
{
	//chinh mau nen thanh den
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//cho toan man hinh thanh xam
	SDL_RenderClear(renderer);

	drawStatusLives(game);
}

void screenContain(SDL_Renderer* renderer, GameState* game)
{
	//Draw background
	SDL_Rect rect_bg = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderCopy(renderer, game->backGr, NULL, &rect_bg);

	//Draw bircks
	for (int i = 0; i < game->numBrick; i++)
	{
		SDL_Rect rect = { game->scrollX + game->bricks[i]->x, game->bricks[i]->y, game->bricks[i]->w, game->bricks[i]->h };
		SDL_RenderCopy(renderer, game->IMGbrick, NULL, &rect);
	}

	//Draw Score
	char* str = (char*)malloc(30, sizeof(char));
	sprintf_s(str, 30, "SCORE: %d", game->player.score);

	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface* tmp = TTF_RenderText_Blended(game->font, str, white);
	game->label_h = tmp->h;
	game->label_w = tmp->w;
	game->label = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	free(str);
	SDL_Rect textRect = { 0, 0, game->label_w, game->label_h };
	SDL_RenderCopy(renderer, game->label, NULL, &textRect);

	//Draw enemies
	for (int i = 0; i < game->numEnemies; i++)
	{
		if (game->enemies[i] != NULL)
		{
			//Set hp color
			SDL_SetRenderDrawColor(renderer, 220, 20, 60, 255);
			if (fabs(game->player.x - game->enemies[i]->x) < 300)
			{
				if (game->enemies[i]->lives == 2) {
					SDL_Rect hpRect = { game->scrollX + game->enemies[i]->x, game->enemies[i]->y - 30, 45, 5 };
					//Draw hp
					SDL_RenderFillRects(renderer, &hpRect, 1);
				}
				else if (game->enemies[i]->lives == 1)
				{
					SDL_Rect hpRect = { game->scrollX + game->enemies[i]->x, game->enemies[i]->y - 30, 22.5, 5 };
					//Draw hp
					SDL_RenderFillRects(renderer, &hpRect, 1);
				}
			}
			SDL_Rect rectE = { game->scrollX + game->enemies[i]->x, game->enemies[i]->y, game->enemies[i]->w, game->enemies[i]->h };

			//Draw enemies
			SDL_RenderCopyEx(renderer, game->IMGenemies, NULL, &rectE, 0, NULL, game->enemies[i]->flipChar);
		}
	}
	//Draw enemies short
	for (int i = 0; i < game->numEnemiesShort; i++)
	{
		if (game->enemiesShort[i] != NULL)
		{
			SDL_SetRenderDrawColor(renderer, 220, 20, 60, 255); // Set color of heath point
			if (fabs(game->player.x - game->enemiesShort[i]->x) < 300 && game->enemiesShort[i]->valid == 1)
			{
				SDL_Rect hpRect2 = { game->scrollX + game->enemiesShort[i]->x, game->enemiesShort[i]->y - 30, 45, 5 };
				//Draw hp
				SDL_RenderFillRects(renderer, &hpRect2, 1);
			}
			SDL_Rect rectES = { game->scrollX + game->enemiesShort[i]->x, game->enemiesShort[i]->y, game->enemiesShort[i]->w, game->enemiesShort[i]->h };
			SDL_Rect scrRectES = { 48 * game->enemiesShort[i]->xAni, 48 * game->enemiesShort[i]->yAni , game->enemiesShort[i]->w, game->enemiesShort[i]->h };

			//Draw enemies
			SDL_RenderCopyEx(renderer, game->IMGenemiesShort, &scrRectES, &rectES, 0, NULL, game->enemiesShort[i]->flipChar);
		}
	}

	//Draw boss
	for (int i = 0; i < game->numBoss; i++)
	{
		if (game->boss[i] != NULL)
		{
			SDL_SetRenderDrawColor(renderer, 220, 20, 60, 255); // Set color of heath point
			if (fabs(game->player.x - game->boss[i]->x) < SCREEN_WIDTH )
			{
				SDL_Rect hpRectBoss = { game->scrollX + game->boss[i]->x + game->boss[i]->w /2 - game->boss[i]->lives, game->boss[i]->y - 100, 2 * game->boss[i]->lives, 7};
				//Draw hp
				SDL_RenderFillRects(renderer, &hpRectBoss, 1);
			}
			SDL_Rect rectES = { game->scrollX + game->boss[i]->x, game->boss[i]->y, game->boss[i]->w, game->boss[i]->h };
			SDL_Rect scrRectES = { 360 * game->boss[i]->xAni, 0, game->boss[i]->w, game->boss[i]->h };

			//Draw enemies
			SDL_RenderCopyEx(renderer, game->IMGBoss, &scrRectES, &rectES, 0, NULL, game->boss[i]->flipChar);
		}
	}

	//Draw coin
	for (int i = 0; i < game->numCoin; i++)
	{
		if (game->coin[i])
		{
			SDL_Rect rectCoin = { game->scrollX + game->coin[i]->x, game->coin[i]->y, game->coin[i]->w, game->coin[i]->h};
			SDL_Rect scrRectCoin = { 800 * game->coin[i]->xAni, game->coin[i]->yAni * 800, 800, 800 };
			SDL_RenderCopyEx(renderer, game->IMGCoin, &scrRectCoin, &rectCoin, 0, 0, 0);
		}
	}

	//Draw CheckPoint
	for (int i = 0; i < game->numCheckPoint; i++)
	{
		if (game->checkpoint[i])
		{
			SDL_Rect rectCheck = { game->scrollX + game->checkpoint[i]->x, game->checkpoint[i]->y, game->checkpoint[i]->w, game->checkpoint[i]->h };
			SDL_RenderCopy(renderer, game->IMGcheckpoint, NULL, &rectCheck);
		}
	}

	//Draw player
	SDL_Rect rect_p = { game->scrollX + game->player.x, game->player.y, game->player.w, game->player.h };
	SDL_Rect scrRect_p = { 33 * game->player.xAni, 27 * game->player.yAni, 33, 27 };
	SDL_RenderCopyEx(renderer, game->IMGPlayer, &scrRect_p, &rect_p, 0, NULL, game->player.flipChar);
	

	//Draw bullet

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (game->bullets[i])
		{
			SDL_Rect rectBu = { game->scrollX + game->bullets[i]->x, game->bullets[i]->y, 8, 8 };
			SDL_RenderCopy(renderer, game->IMGbullet, NULL, &rectBu);
		}
	}

	//Draw bullet of enemies
	for (int i = 0; i < MAX_BULLETS_ENEMIES; i++)
	{
		if (game->bulletEnemies[i])
		{
			SDL_Rect rectBuE = { game->scrollX + game->bulletEnemies[i]->x, game->bulletEnemies[i]->y, 8, 8 };
			SDL_RenderCopy(renderer, game->IMGbullet, NULL, &rectBuE);
		}
	}
	//Draw bullet of boss
	for (int i = 0; i < MAX_BULLETS_BOSS; i++)
	{
		if (game->bulletBoss[i])
		{
			SDL_Rect rectBuB = { game->scrollX + game->bulletBoss[i]->x, game->bulletBoss[i]->y, 10, 10 };
			SDL_RenderCopy(renderer, game->IMGbullet, NULL, &rectBuB);
		}
	}
}

void followScreen(GameState* game)
{
	game->scrollX = -game->player.x + SCREEN_WIDTH / 2; //Make sure the screen cannot go over the middle of the screen
	if (game->scrollX > 0)
	{
		game->scrollX = 0; //Cannot seen the left of the map
	}
	if (game->scrollX < -game->bricks[1]->w * 393 + SCREEN_WIDTH / 2)
	{
		game->scrollX = -game->bricks[1]->w * 393 + SCREEN_WIDTH / 2; //Cannot seen the right of the map
	}
}

void drawStatusLives(GameState* game)
{
	//chinh mau cua nen
	SDL_SetRenderDrawColor(game->renderer1, 255, 255, 255, 255);

	//vi tri hinh nhan vat
	SDL_Rect scrRect_p = { 0, 0, 33, 27 };
	SDL_Rect rect_p = { SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 50, 55, 45 };
	SDL_RenderCopyEx(game->renderer1, game->IMGPlayer, &scrRect_p, &rect_p, 0, NULL, 0);

	//ve text
	SDL_Rect textRect = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - game->label_h, game->label_w, game->label_h };
	SDL_RenderCopy(game->renderer1, game->label, NULL, &textRect);

}

void shutdownStatusLives(GameState* game)
{
	SDL_DestroyTexture(game->label);
	game->label = NULL;
}