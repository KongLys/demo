#include "Func.h"

void init_status_lives(GameState* game)
{

	char* str = (char*)malloc(10, sizeof(char));
	sprintf_s(str, 10, "x %d", game->player.lives);

	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface* tmp = TTF_RenderText_Blended(game->font, str, white);
	game->label_h = tmp->h;
	game->label_w = tmp->w;
	game->label = SDL_CreateTextureFromSurface(game->renderer1, tmp);
	SDL_FreeSurface(tmp);
	free(str);
}

void init_status_over(GameState* game)
{

	char str[10] = "GAME OVER";

	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface* tmp = TTF_RenderText_Blended(game->font, str, white);
	game->label_h = tmp->h;
	game->label_w = tmp->w;
	game->label = SDL_CreateTextureFromSurface(game->renderer1, tmp);
	SDL_FreeSurface(tmp);
}

void draw_status_lives(GameState* game)
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

void draw_status_over(GameState* game)
{
	//chinh mau cua nen
	SDL_SetRenderDrawColor(game->renderer1, 255, 255, 255, 255);

	//ve text
	SDL_Rect textRect = { SCREEN_WIDTH / 2 - game->label_w/2, SCREEN_HEIGHT / 2 - game->label_h, game->label_w, game->label_h };
	SDL_RenderCopy(game->renderer1, game->label, NULL, &textRect);

}

void shutdown_status_lives(GameState* game)
{
	SDL_DestroyTexture(game->label);
	game->label = NULL;
}