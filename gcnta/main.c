#include "Hfunc.h"

int main(int argc, char* argv[]) {
	//init and declare
	GameState gameState;
	SDL_Window* windown = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	windown = SDL_CreateWindow("Game gi do", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(windown, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	gameState.renderer = renderer;

	loadGame(&gameState);

	short done = 0;
	while (!done)
	{
		done = processEvent(windown, &gameState);

		processGameAni(&gameState);

		collisionDetect(&gameState);

		doRenderer(renderer, &gameState);

	}

	//Free and close the program
	SDL_DestroyTexture(gameState.IMGbrick);
	SDL_DestroyTexture(gameState.playerFrames[0]);
	SDL_DestroyTexture(gameState.playerFrames[1]);
	SDL_DestroyTexture(gameState.backGr);
	SDL_DestroyTexture(gameState.IMGenemies);
	SDL_DestroyTexture(gameState.IMGbullet);

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		removeBullet(&gameState, i);
	}
	


	SDL_DestroyWindow(windown);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}