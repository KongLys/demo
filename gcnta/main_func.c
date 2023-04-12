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
			case SDLK_p:
				menuPause(game->renderer1, game->font);
				break;
			case SDLK_ESCAPE:
				done = 1;
				break;

			case SDLK_x:
				if (game->player.onBrick)
				{
					game->player.dy = -8;
					game->player.onBrick = 0;
					jumbSound();
				}
				break;
			case SDLK_k:
				if (game->player.onBrick)
				{
					game->player.dy = -8;
					game->player.onBrick = 0;
					jumbSound();
				}
				break;
			case SDLK_z:
			case SDLK_l:
				if (game->player.dashCoolDown == 0)
				{
					if (game->player.flipChar == 0)
					{
						game->player.dashPower = 5;
					}
					else
					{
						game->player.dashPower = -5;
					}

					game->player.dashCoolDown = 35;
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
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
	{
		game->player.angle = -45;
		game->player.aiming = 1;
	}
	else if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
	{
		game->player.angle = 45;
		game->player.aiming = 2;
	}
	else
	{
		game->player.aiming = 0;
	}
	if (state[SDL_SCANCODE_X] || state[SDL_SCANCODE_K])
	{
		game->player.dy -= 0.3;
		if (game->player.dy < -9)
		{
			game->player.dy = -9;
		}
		game->player.yAni = 5;
	}
	if (state[SDL_SCANCODE_C] || state[SDL_SCANCODE_J])
	{
		game->player.shootBullet = 1;
		if (game->time % 5 == 0)
		{
			addBullet(game);
		}
		if (game->player.aiming == 1)
		{
			game->player.yAni = 3;
		}
		else if (game->player.aiming == 2)
		{
			game->player.yAni = 4;
		}
		else
		{
			game->player.yAni = 2;
		}
		shotSound();
	}
	else
	{
		game->player.shootBullet = 0;
	}
	if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
	{
		if (game->player.onBrick == 1)
		{
			walkingSound();
		}
		game->player.dx -= 2;
		if (game->player.dx <= -5)
		{
			game->player.dx = -5;
		}
		game->player.flipChar = 1;
		game->player.stopMove = 0;
		if (!game->player.shootBullet)
		{
			game->player.yAni = 1;
		}
	}
	else if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
	{
		if (game->player.onBrick == 1)
		{
			walkingSound();
		}
		game->player.dx += 2;
		if (game->player.dx >= 5)
		{
			game->player.dx = 5;
		}
		game->player.flipChar = 0;
		game->player.stopMove = 0;
		if (!game->player.shootBullet)
		{
			game->player.yAni = 1;
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
	}
	return done;
}




void processGame(GameState* game)
{
	game->time++;
	if (game->time > 120)
	{
		shutdownStatusLives(game);
		game->status = GAME_PLAY;
	}
	//Set game play
	if (game->status == GAME_PLAY)
	{
		//Set dash cd
		if (game->player.dashCoolDown > 0)
		{
			game->player.dashCoolDown--;
		}

		//Set animation
		if (!game->player.shootBullet)
		{
			if (game->player.stopMove)
			{
				game->player.yAni = 0;
			}
			else
			{
				game->player.yAni = 1;
			}
		}
		if (game->time % 6 == 0)
		{
			game->player.xAni++;
			if (game->player.yAni == 4 || game->player.yAni == 3 || game->player.yAni == 2)
			{
				if (game->player.xAni > 4)
				{
					game->player.xAni = 3;
				}
			}
			game->player.xAni %= 5;
		}

		//Set angle shooting
		if (!game->player.aiming)
		{
			game->player.angle = 0;
		}

		//Speed
		game->player.x += (game->player.dx + game->player.dashPower);
		if (game->player.dashCoolDown > 25)
		{
			game->player.dashPower *= 1.25;
		}
		else
		{
			game->player.dashPower = 0;
		}
		game->player.y += game->player.dy;
		game->player.dy += GRAVITY;


		//Movement of enemies
		movementEnemies(game);
		movementEnemiesShort(game);
		aniEnemiesShort(game);

		//Process bullet of player
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (game->bullets[i])
			{
				game->bullets[i]->x += game->bullets[i]->dx;
				game->bullets[i]->y += game->bullets[i]->dy;
				if (checkBullets(game, i) == 1)
				{
					removeBullet(game, i);
				}
			}
		}

		//Process bullet of enemies

		for (int i = 0; i < MAX_BULLETS_ENEMIES; i++)
		{
			if (game->bulletEnemies[i])
			{
				game->bulletEnemies[i]->x += game->bulletEnemies[i]->dx;
				game->bulletEnemies[i]->y += game->bulletEnemies[i]->dy;
				if (checkBulletEnemies(game, i) == 1)
				{
					removeBulletEnemies(game, i);
				}
			}
		}
		bossShoot(game);
		//Process bullet of boss
		for (int i = 0; i < MAX_BULLETS_BOSS; i++)
		{
			if (game->bulletBoss[i])
			{
				game->bulletBoss[i]->x += game->bulletBoss[i]->dx;
				game->bulletBoss[i]->y += game->bulletBoss[i]->dy;
				if (checkBulletBoss(game, i) == 1)
				{
					removeBulletBoss(game, i);
				}
			}
		}

		//follow
		followScreen(game);

		//Collision
		collisionPlayerWithCoin(game);
		collisionDetect(game);
	}

	//When player touch enemies
	if (collisionPlayerWithEnnemies(game) == 1 || collisionPlayerWithEnnemiesShort(game) == 1 || game->player.hit == 1)
	{
		game->player.hit = 0;
		dameSound();
		//Free and reload
		for (int i = 0; i < game->numEnemies; i++)
		{
			if (game->enemies[i])
			{
				removeEnemies(game, i);
			}
		}
		for (int i = 0; i < game->numEnemiesShort; i++)
		{
			if (game->enemiesShort[i])
			{
				removeEnemiesShort(game, i);
			}
		}
		loadAgain(game);
		initStatusLives(game);
	}
	if (game->player.lives <= 0)
	{
		short done = 1;
		game->player.lives = 3;
		menuED(game->renderer1, game->font, done, game);
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
	else if (game->status == GAME_OVER)
	{
		scrennOver(renderer, game);
	}
	//Show renderer
	SDL_RenderPresent(renderer);
}
