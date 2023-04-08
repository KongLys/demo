#include "main_func.h"

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
				game->player.dy = -8;
				game->player.onBrick = 0;
				jumbSound();
				}
				break;
			case SDLK_w:
				if (game->player.onBrick)
				{
					game->player.dy = -8;
					game->player.onBrick = 0;
					jumbSound();
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
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
	{
			game->player.dy -= 0.3;
			if (game->player.dy < -9)
			{
				game->player.dy = -9;
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
		shotSound();
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




void processGame(GameState* game)
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
		shutdownStatusLives(game);
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

		//Speed
		game->player.x += game->player.dx;
		game->player.y += game->player.dy;
		game->player.dy += GRAVITY;
		
		//follow
		followScreen(game);

		//Movement of enemies
		movementEnemies(game);
	}

	//Reload info
	if (collisionPlayerWithEnnemies(game) == 1)
	{
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (game->enemies[i] != NULL)
			{
				removeEnemies(game, i);
			}
		}
		loadAgain(game);
		initStatusLives(game);
	}
	if(game->player.lives <= 0)
	{
		short done = 1;
		game->player.lives = 3;
		menuED(game->renderer1, game->font, done);
	}
}

void doRenderer(SDL_Renderer* renderer, GameState* game)
{
	if (game->status == GAME_NEW)
	{
		screenStart(renderer, game);
	}
	else if (game->status == GAME_PLAY)
	{
		screenContain(renderer, game);
	}
	else if(game->status == GAME_OVER)
	{
		scrennOver(renderer, game);
	}
		//Show renderer
		SDL_RenderPresent(renderer);
}
