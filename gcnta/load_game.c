#include "load_game.h"

void loadGame(GameState* game)
{
	//Load brick
	SDL_Surface* surface;
	surface = IMG_Load("brick.jfif");
	if (surface == NULL)
	{
		printf("Cannot find brick.jfif! \n\n");
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
	//load fonts
	game->font = TTF_OpenFont("victor-pixel.ttf", 48);
	if (!game->font)
	{
		printf("Cannot find font file! \n\n");
		SDL_Quit();
		exit(1);
	}

	//Load info player
	game->player.x = 50;
	game->player.y = 650;
	game->player.w = 64;
	game->player.h = 64;
	game->player.dx = 0;
	game->player.dy = 0;
	game->player.lives = 3;
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

	//Load position of enemies
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		game->enemies[i] = (Enemy*)malloc(sizeof(Enemy));
		game->enemies[i]->x = 500 * (i+1);
		game->enemies[i]->y = 700;
		game->enemies[i]->w = 64;
		game->enemies[i]->h = 64;
		game->enemies[i]->dx = 2;
		game->enemies[i]->dy = 2;
		game->enemies[i]->flipChar = 1;
		game->enemies[i]->lives = 2;
	}

	for (int i = 0; i < NUM_ENEMIES_2; i++)
	{
		game->enemiesShort[i] = (EnemyShort*)malloc(sizeof(EnemyShort));
		game->enemiesShort[i]->x = 650 * (i + 1);
		game->enemiesShort[i]->y = 700;
		game->enemiesShort[i]->w = 48;
		game->enemiesShort[i]->h = 48;
		game->enemiesShort[i]->dx = 2;
		game->enemiesShort[i]->dy = 0;
		game->enemiesShort[i]->xAni = 0;
		game->enemiesShort[i]->yAni = 1;
		game->enemiesShort[i]->valid = 1;
		game->enemiesShort[i]->flipChar = 1;
		game->enemiesShort[i]->lives = 1;
	}

	//Load position of bricks
	for (int i = 0; i < NUM_PBRICK; i++)
	{
		game->bricks[i].x = i * 500;
		game->bricks[i].y = 750;
		game->bricks[i].w = 500;
		game->bricks[i].h = 100;
	}
	game->bricks[99].x = 500 * 98;
	game->bricks[99].y = 0;
	game->bricks[99].w = 1;
	game->bricks[99].h = SCREEN_HEIGHT;

	game->bricks[98].x = 0;
	game->bricks[98].y = 0;
	game->bricks[98].w = 1;
	game->bricks[98].h = SCREEN_HEIGHT;

	game->bricks[97].x = 650;
	game->bricks[97].y = 520;
	game->bricks[97].w = 500;
	game->bricks[97].h = 100;
}

void loadAgain(GameState* game)
{
	game->player.x = 50;
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

	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		game->enemies[i] = (Enemy*)malloc(sizeof(Enemy));
		game->enemies[i]->x = 500 * (i+1);
		game->enemies[i]->y = 700;
		game->enemies[i]->w = 64;
		game->enemies[i]->h = 64;
		game->enemies[i]->dx = 2;
		game->enemies[i]->dy = 2;
		game->enemies[i]->flipChar = 1;
		game->enemies[i]->lives = 2;
	}
	for (int i = 0; i < NUM_ENEMIES_2; i++)
	{
		game->enemiesShort[i] = (EnemyShort*)malloc(sizeof(EnemyShort));
		game->enemiesShort[i]->x = 650 * (i + 1);
		game->enemiesShort[i]->y = 700;
		game->enemiesShort[i]->w = 48;
		game->enemiesShort[i]->h = 48;
		game->enemiesShort[i]->dx = 2;
		game->enemiesShort[i]->dy = 0;
		game->enemiesShort[i]->xAni = 0;
		game->enemiesShort[i]->yAni = 1;
		game->enemiesShort[i]->valid = 1;
		game->enemiesShort[i]->flipChar = 1;
		game->enemiesShort[i]->lives = 1;
	}
}
