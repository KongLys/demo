#include "load_game.h"

void loadGame(GameState* game)
{
	//Load brick
	SDL_Surface* surface;
	surface = IMG_Load("brick.png");
	if (surface == NULL)
	{
		printf("Cannot find brick.png! \n\n");
		SDL_Quit();
		exit(1);
	}
	game->IMGbrick = SDL_CreateTextureFromSurface(game->renderer1, surface);
	SDL_FreeSurface(surface);

	//Load character
	surface = IMG_Load("waiting.png");
	if (surface == NULL)
	{
		printf("robot.jpg! \n\n");
		SDL_Quit();
		exit(1);
	}
	game->playerFrames[0] = SDL_CreateTextureFromSurface(game->renderer1, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("walk.png");
	if (surface == NULL)
	{
		printf("robot2.jpg! \n\n");
		SDL_Quit();
		exit(1);
	}
	game->playerFrames[1] = SDL_CreateTextureFromSurface(game->renderer1, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("cut.png");
	if (surface == NULL)
	{
		printf("robot2.jpg! \n\n");
		SDL_Quit();
		exit(1);
	}
	game->playerFrames[2] = SDL_CreateTextureFromSurface(game->renderer1, surface);
	SDL_FreeSurface(surface);

	//Load background
	surface = IMG_Load("backgr.png");
	if (surface == NULL)
	{
		printf("rCyberpunk City Pixel Art.jpg! \n\n");
		SDL_Quit();
		exit(1);
	}
	game->backGr = SDL_CreateTextureFromSurface(game->renderer1, surface);
	SDL_FreeSurface(surface);

	//Load enemies
	surface = IMG_Load("beeRobotR.png");
	if (surface == NULL)
	{
		printf("beeRobotR.png! \n\n");
		SDL_Quit();
		exit(1);
	}
	game->IMGenemies = SDL_CreateTextureFromSurface(game->renderer1, surface);
	SDL_FreeSurface(surface);

	//Load enemies short
	surface = IMG_Load("enemiesShort.png");
	if (surface == NULL)
	{
		printf("enemiesShort.png!\n\n");
		SDL_Quit();
		exit(1);
	}
	game->IMGenemiesShort = SDL_CreateTextureFromSurface(game->renderer1, surface);
	SDL_FreeSurface(surface);

	//Load bullet
	surface = IMG_Load("ballr.png");
	if (surface == NULL)
	{
		printf("ballr.png! \n\n");
		SDL_Quit();
		exit(1);
	}
	game->IMGbullet = SDL_CreateTextureFromSurface(game->renderer1, surface);
	SDL_FreeSurface(surface);
	
	//Load coin
	surface = IMG_Load("coin.png");
	if (surface == NULL)
	{
		printf("coin.png! \n\n");
		SDL_Quit();
		exit(1);
	}
	game->IMGCoin = SDL_CreateTextureFromSurface(game->renderer1, surface);
	SDL_FreeSurface(surface);

	//load fonts
	game->font = TTF_OpenFont("victor-pixel.ttf", 48);
	if (!game->font)
	{
		printf("Cannot find font file! \n\n");
		SDL_Quit();
		exit(1);
	}

	//Load info player
	game->player.x = 250;
	game->player.y = 10;
	game->player.w = 64;
	game->player.h = 64;
	game->player.dx = 0;
	game->player.dy = 0;
	game->player.lives = 3;
	game->player.hit = 0;
	game->player.animFrame = 0;
	game->player.flipChar = 0;
	game->player.onBrick = 0;
	game->player.shootBullet = 0;
	game->player.stopMove = 1;
	game->player.currentCut = 0;
	game->player.currentWait = 0;
	game->player.currentWalk = 0;


	//Load info GameState
	game->scrollX = 0;
	game->time = 0;
	game->label = NULL;
	game->status = GAME_NEW;

	//Load screen
	initStatusLives(game);

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		game->bullets[i] = NULL;
	}

	for (int i = 0; i < MAX_BULLETS_ENEMIES; i++)
	{
		game->bulletEnemies[i] = NULL;
	}

	//Count bricks, enemies, short enemies
	game->numBrick = cntBrick(game);
	game->numEnemies = cntEnemies(game);
	game->numEnemiesShort = cntEnemiesShort(game);
	game->numCoin = cntCoin(game);

	//Load bricks, enemies, short enemies
	loadEnemies(game);
	loadEnemiesShort(game);
	loadCoin(game);
	loadMap(game);
}

void loadAgain(GameState* game)
{
	game->player.x = 250;
	game->player.y = 650;
	game->player.w = 64;
	game->player.h = 64;
	game->player.dx = 0;
	game->player.dy = 0;
	game->player.animFrame = 0;
	game->player.flipChar = 0;
	game->player.onBrick = 0;
	game->player.shootBullet = 0;
	game->player.stopMove = 1;
	game->player.currentCut = 0;
	game->player.currentWait = 0;
	game->player.currentWalk = 0;

	game->scrollX = 0;
	game->time = 0;

	game->status = GAME_NEW;

	loadEnemies(game);
	loadEnemiesShort(game);
	loadCoin(game);
}
