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

	//Load CheckPoint
	surface = IMG_Load("check_points.jpg");
	if (surface == NULL)
	{
		printf("Cannot find check_points.jpg! \n\n");
		SDL_Quit();
		exit(1);
	}
	game->IMGcheckpoint= SDL_CreateTextureFromSurface(game->renderer1, surface);
	SDL_FreeSurface(surface);

	//Load character
	surface = IMG_Load("player.png");
	if (surface == NULL)
	{
		printf("player.png! \n\n");
		SDL_Quit();
		exit(1);
	}
	game->IMGPlayer = SDL_CreateTextureFromSurface(game->renderer1, surface);
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
	surface = IMG_Load("fly.png");
	if (surface == NULL)
	{
		printf("fly.png! \n\n");
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

	//Load info player

	game->player.x = 250;
	game->player.y = 10;
	game->player.w = 33;
	game->player.h = 27;
	game->player.dx = 0;
	game->player.dy = 0;
	game->player.dashCoolDown = 0;
	game->player.dashPower = 0;
	game->player.angle = 0;
	game->player.lives = 3;
	game->player.hit = 0;
	game->player.xAni = 0;
	game->player.yAni = 0;
	game->player.aiming = 0;
	game->player.flipChar = 0;
	game->player.onBrick = 0;
	game->player.shootBullet = 0;
	game->player.stopMove = 1;

	game->player.currentCut = 0;
	game->player.currentWait = 0;
	game->player.currentWalk = 0;
	if (game->continueGame)
	{
		take_process(game);
	}

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
	for (int i = 0; i < MAX_BULLETS_BOSS; i++)
	{
		game->bulletBoss[i] = NULL;
	}

	//Count bricks, enemies, short enemies, check points
	game->numBrick = cntBrick(game);
	game->numEnemies = cntEnemies(game);
	game->numEnemiesShort = cntEnemiesShort(game);
	game->numCoin = cntCoin(game);
	game->numCheckPoint = cntCheckPoint(game);
	game->numBoss = cntBoss(game);

	//Load bricks, enemies, short enemies, check point
	loadEnemies(game);
	loadEnemiesShort(game);
	loadBoss(game);
	loadCoin(game);
	loadCheckPoint(game);
	loadMap(game);
}

void save_process(GameState* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "save_process.txt", "w");
	fprintf_s(fp, "%f\n%f\n%d\n", game->player.x, game->player.y, game->player.lives);
	fclose(fp);// là á, t chưa có gọi cái hàm save_process này ở đâu, nhma khi chết nó vẫn lấy tọa đọ của xy để nó đọc lại
}

short take_process(GameState* game)
{
	FILE* fp = NULL;
	int num_values_read = 0;
	fopen_s(&fp, "save_process.txt", "r");
	if (fp == NULL)
	{
		printf("Error!");
		exit(1);
	}

	num_values_read = fscanf_s(fp, "%f%f%d", &game->player.x, &game->player.y, &game->player.lives);
	fclose(fp);
	if (num_values_read == 0) {
		return 0;
	}
	else {
		return num_values_read;
	}	
}

void readXY(GameState* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "save_process.txt", "r");
	if (fp == NULL)
	{
		printf("Error!");
		exit(1);
	}
	int num_values_read;
	num_values_read = fscanf_s(fp, "%f%f", &game->player.x, &game->player.y);
	fclose(fp);
	if (num_values_read == 0) {
		return 0;
	}
	else {
		return num_values_read;
	}
	
}

void loadAgain(GameState* game)
{
	readXY(game);
	game->player.w = 64;
	game->player.h = 64;
	game->player.dx = 0;
	game->player.dy = 0;
	game->player.dashCoolDown = 0;
	game->player.angle = 0;
	game->player.hit = 0;
	game->player.xAni = 0;
	game->player.yAni = 0;
	game->player.aiming = 0;
	game->player.flipChar = 0;
	game->player.onBrick = 0;
	game->player.shootBullet = 0;
	game->player.stopMove = 1;

	game->scrollX = 0;
	game->time = 0;

	game->status = GAME_NEW;

	loadEnemies(game);
	loadEnemiesShort(game);
	loadBoss(game);
	loadCoin(game);
	loadCheckPoint(game);
}
 
