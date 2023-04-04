#include "screen_status.h"

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

void initStatusOver(GameState* game)
{

	char str[10] = "GAME OVER";

	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface* tmp = TTF_RenderText_Blended(game->font, str, white);
	game->label_h = 100;
	game->label_w = 200;
	game->label = SDL_CreateTextureFromSurface(game->renderer1, tmp);
	SDL_FreeSurface(tmp);
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
	for (int i = 0; i < NUM_PBRICK; i++)
	{
		SDL_Rect rect = { game->scrollX + game->bricks[i].x, game->bricks[i].y, game->bricks[i].w, game->bricks[i].h };
		SDL_RenderCopy(renderer, game->IMGbrick, NULL, &rect);
	}

	//Draw enemies
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		if (game->enemies[i] != NULL)
		{
			//Draw something
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
	//Draw player
	SDL_Rect rect_p = { game->scrollX + game->player.x, game->player.y, game->player.w, game->player.h };
	if (game->player.animFrame == 2)
	{
		SDL_Rect scrRect_p = { 43 * game->player.currentCut, 0, 43, 37 };
		SDL_RenderCopyEx(renderer, game->playerFrames[game->player.animFrame], &scrRect_p, &rect_p, 0, NULL, game->player.flipChar);
	}
	else if (game->player.animFrame == 1)
	{
		SDL_Rect scrRect_p = { 22 * game->player.currentWalk, 0 , 22, 33 };
		SDL_RenderCopyEx(renderer, game->playerFrames[game->player.animFrame], &scrRect_p, &rect_p, 0, NULL, game->player.flipChar);
	}
	else
	{
		SDL_Rect scrRect_p = { 24 * game->player.currentWait, 0, 24, 32 };
		SDL_RenderCopyEx(renderer, game->playerFrames[game->player.animFrame], &scrRect_p, &rect_p, 0, NULL, game->player.flipChar);
	}



	//Draw bullet

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (game->bullets[i])
		{
			SDL_Rect rectBu = { game->scrollX + game->bullets[i]->x, game->bullets[i]->y, 16, 16 };
			SDL_RenderCopy(renderer, game->IMGbullet, NULL, &rectBu);
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
	if (game->scrollX < -game->bricks[1].w * (NUM_PBRICK - 30) + SCREEN_WIDTH / 2)
	{
		game->scrollX = -game->bricks[1].w * (NUM_PBRICK - 30) + SCREEN_WIDTH / 2; //Cannot seen the right of the map
	}
}

void scrennOver(SDL_Renderer* renderer, GameState* game)
{
	//chinh mau nen thanh den
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//cho toan man hinh thanh xam
	SDL_RenderClear(renderer);

	drawStatusOver(game);
}

void drawStatusLives(GameState* game)
{
	//chinh mau cua nen
	SDL_SetRenderDrawColor(game->renderer1, 255, 255, 255, 255);

	//vi tri hinh nhan vat
	SDL_Rect scrRect_p = { 0, 0, 24, 32 };
	SDL_Rect rect_p = { SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 50, 48, 48 };
	SDL_RenderCopyEx(game->renderer1, game->playerFrames[0], &scrRect_p, &rect_p, 0, NULL, 0);

	//ve text
	SDL_Rect textRect = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - game->label_h, game->label_w, game->label_h };
	SDL_RenderCopy(game->renderer1, game->label, NULL, &textRect);

}

void drawStatusOver(GameState* game)
{
	//chinh mau cua nen
	SDL_SetRenderDrawColor(game->renderer1, 255, 255, 255, 255);

	//ve text
	SDL_Rect textRect = { SCREEN_WIDTH / 2 - game->label_w/2, SCREEN_HEIGHT / 2 - game->label_h, game->label_w, game->label_h };
	SDL_RenderCopy(game->renderer1, game->label, NULL, &textRect);

}

void shutdownStatusLives(GameState* game)
{
	SDL_DestroyTexture(game->label);
	game->label = NULL;
}