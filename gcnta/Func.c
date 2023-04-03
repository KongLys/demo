#include "Func.h"

void loadGame(GameState* game)
{
	//Load brick
	SDL_Surface *surface;
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
	game->player.y = 50;
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
	init_status_lives(game);

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		game->bullets[i] = NULL;
	}

	//Load position of brick
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		game->enemies[i] = (Enemy*)malloc(sizeof(Enemy));
		game->enemies[i]->x = 500* i;
		game->enemies[i]->y = 700;
		game->enemies[i]->w = 64;
		game->enemies[i]->h = 64;
		game->enemies[i]->dx = 2;
		game->enemies[i]->flipChar = 1;
		game->enemies[i]->lives = 2;

	}
	game->enemies[49]->x = 550;

	game->enemies[0]->x = 450;

	//Load position of enemies

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
	
	game->bricks[97].x = 1500;
	game->bricks[97].y = 520;
	game->bricks[97].w = 100;
	game->bricks[97].h = 100;
}

void loadAgain(GameState* game)
{
	game->player.x = 50;
	game->player.y = 50;
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
		game->enemies[i]->x = 500 * i;
		game->enemies[i]->y = 700;
		game->enemies[i]->w = 64;
		game->enemies[i]->h = 64;
		game->enemies[i]->dx = 2;
		game->enemies[i]->flipChar = 1;
		game->enemies[i]->lives = 2;

	}
	game->enemies[49]->x = 550;

	game->enemies[0]->x = 450;
}

int processEvent(SDL_Window* windown, GameState* game)
{
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	short done = 0;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_WINDOWEVENT_CLOSE:
		{
			if (windown)
			{
				SDL_DestroyWindow(windown);
				windown = NULL;
				done = 1;
			}
		}
		break;
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				done = 1;
				break;

			case SDLK_UP:
				if(game->player.onBrick)
				{
				game->player.dy -= 8;
				game->player.onBrick = 0;
				}
				break;
			case SDLK_w:
				if (game->player.onBrick)
				{
					game->player.dy -= 8;
					game->player.onBrick = 0;
				}
				break;
			}

		}
		break;
		case SDL_QUIT:
			//quit the game
			done = 1;
			break;
		}
	}
	//Hold key
	if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
	{
		game->player.dy += 0.6;
		if (game->player.dy > 10)
		{
			game->player.dy = 10;
		}
	}
	else if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
	{
		game->player.dy -= 0.3;
		if (game->player.dy < -10)
		{
			game->player.dy = -10;
		}
	}
	if (state[SDL_SCANCODE_SPACE])
	{
		game->player.shootBullet = 1;
		if (game->time % 5 == 0) 
		{
			addBullet(game);
		}
		game->player.currentCut = 1;
	}
	else
	{
		game->player.shootBullet = 0;
	}
	if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
	{
		game->player.dx -= 2;
		if (game->player.dx <= -5)
		{
			game->player.dx = -5;
		}
		game->player.flipChar = 1;
		game->player.stopMove = 0;
		game->player.animFrame = 1;
		if (game->time % 6 == 0)
		{
			game->player.currentWalk++;
			game->player.currentWalk %= 13;
		}
	}
	else if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
	{
		game->player.dx += 2;
		if (game->player.dx >= 5)
		{
			game->player.dx = 5;
		}
		game->player.flipChar = 0;
		game->player.stopMove = 0;
		game->player.animFrame = 1;
		if (game->time % 6 == 0)
		{
			game->player.currentWalk++;
			game->player.currentWalk %= 13;
		}
	}
	else
	{
		game->player.dx *= 0.8;
		if (fabs(game->player.dx) <= 1)
		{
			game->player.dx = 0;
		}
		game->player.stopMove = 1;
		game->player.animFrame = 0;
	}
	return done;
}

void removeEnemies(GameState* game, int i)
{
	free(game->enemies[i]);
	game->enemies[i] = NULL;
}


void processGameAni(GameState* game)
{
	game->time++;

	//Wait animation
	if (game->time % 5 == 0 && game->player.onBrick && game->player.stopMove)
	{
		game->player.currentWait++;
		game->player.currentWait %= 11;
	}

	//set waiting
	if (!game->player.onBrick)
	{
		game->player.animFrame = 0;
	}

	if (game->time > 120)
	{
		shutdown_status_lives(game);
		game->status = GAME_PLAY;
	}

	if (game->status == GAME_PLAY)
	{
		//Cut animation
		//if (game->player.currentCut != 0)
		//{
		//	if (game->time % 5 == 0)
		//	{
		//		game->player.currentCut++;
		//		game->player.currentCut %= 18;
		//	}
		//}

		//Process bullet
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (game->bullets[i])
			{
				game->bullets[i]->x += game->bullets[i]->dx;
				if (checkBullets(game, i) == 1)
				{
					removeBullet(game, i);
				}
			}

		}

		//Movement of enemies
		for (int i = 0; i < NUM_ENEMIES; i++)
		{
			if (game->enemies[i])
			{
				game->enemies[i]->x += game->enemies[i]->dx;
				if (game->time % 127 == 0)
				{
					game->enemies[i]->dx *= -1;
					game->enemies[i]->flipChar = 0;
				}
				else if (game->time % 251 == 0)
				{
					game->enemies[i]->dx *= -1;
					game->enemies[i]->flipChar = 1;

				}
				else if (fabs(game->player.x - game->enemies[i]->x) < 200 && game->player.x < game->enemies[i]->x) //Left
				{
					game->enemies[i]->dx = -4;
					game->enemies[i]->flipChar = 0;

				}
				else if (fabs(game->player.x - game->enemies[i]->x) < 200 && game->player.x > game->enemies[i]->x) //Right
				{
					game->enemies[i]->dx = 4;
					game->enemies[i]->flipChar = 1;

				}
			}
		}
	}

	//screen game over
	if (collision_with_ennemies(game) == 1)
	{
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (game->enemies[i] != NULL)
			{
				removeEnemies(game, i);
			}
		}
		loadAgain(game);
		init_status_lives(game);
	}

	if (game->player.lives <= 0)
	{
		game->status = GAME_OVER;
		init_status_over(game);
	}

	//Speed
	game->player.x += game->player.dx;
	game->player.y += game->player.dy;
	game->player.dy += GRAVITY;

	game->scrollX = -game->player.x + SCREEN_WIDTH / 2; //Make sure the screen cannot go over the middle of the screen
	if (game->scrollX > 0)
	{
		game->scrollX = 0; //Cannot seen the left of the map
	}
	if (game->scrollX < -game->bricks[1].w * (NUM_PBRICK-30) + SCREEN_WIDTH/2 )
	{
		game->scrollX = -game->bricks[1].w * (NUM_PBRICK-30) + SCREEN_WIDTH/2; //Cannot seen the right of the map
	}
}

void doRenderer(SDL_Renderer* renderer, GameState* game)
{
	if (game->status == GAME_NEW)
	{
		//chinh mau nen thanh den
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		//cho toan man hinh thanh xam
		SDL_RenderClear(renderer);

		draw_status_lives(game);
	}
	else if (game->status == GAME_PLAY)
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
				SDL_Rect rectBu = { game->scrollX + game->bullets[i]->x, game->bullets[i]->y, 8, 8 };
				SDL_RenderCopy(renderer, game->IMGbullet, NULL, &rectBu);
			}
		}
	}
	else if(game->status == GAME_OVER)
	{
		//chinh mau nen thanh den
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		//cho toan man hinh thanh xam
		SDL_RenderClear(renderer);

		draw_status_over(game);
	}
		//Show renderer
		SDL_RenderPresent(renderer);
}

