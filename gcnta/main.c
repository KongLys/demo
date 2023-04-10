﻿#include "main_func.h"

int main(int argc, char* argv[]) {
	//init and declare
	GameState gameState;
	SDL_Window* windown = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	windown = SDL_CreateWindow("Game gi do", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(windown, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (initAudio() != 0) {
		printf("Failed to initialize audio!");
		return 1;
	}

	TTF_Init();
	TTF_Font* font = TTF_OpenFont("Take-Coffee.ttf", 32);

	gameState.renderer1 = renderer;
	
	loadGame(&gameState);
	short done = 0;
	menuOP(renderer, font, done);
	
	while (!done)
	{
		done = processEvent(windown, &gameState);

		processGame(&gameState);
		
		collisionDetect(&gameState);

		doRenderer(renderer, &gameState);

	}
	//Free and close the program
	SDL_DestroyTexture(gameState.IMGbrick);
	SDL_DestroyTexture(gameState.playerFrames[0]);
	SDL_DestroyTexture(gameState.playerFrames[1]);
	SDL_DestroyTexture(gameState.playerFrames[2]);
	SDL_DestroyTexture(gameState.backGr);
	SDL_DestroyTexture(gameState.IMGenemies);
	SDL_DestroyTexture(gameState.IMGenemiesShort);
	SDL_DestroyTexture(gameState.IMGbullet);
	SDL_DestroyTexture(gameState.label);

	TTF_CloseFont(gameState.font);
	
	cleanUpAudio();

	SDL_DestroyWindow(windown);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();

	SDL_Quit();

	return 0;
}