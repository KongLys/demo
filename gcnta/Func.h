#pragma once

#include <stdio.h>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT  768 
#define NUM_PBRICK 100
#define NUM_ENEMIES 100
#define MAX_BULLETS 100

#define GRAVITY 0.45

#define GAME_NEW 0
#define GAME_PLAY 1
#define GAME_OVER 2


typedef struct
{
	float  x, y, w, h;
	float dx, dy;
	short animFrame, flipChar, onBrick, stopMove, shootBullet;
	short currentWait, currentWalk, currentCut;
	short lives;
} Player;

typedef struct
{
	float  x, y, w, h;
	float dx;
	short animFrame, flipChar, onBrick, shootBullet;
	short lives;
} Enemy;

typedef struct
{
	float x, y, w ,h;
} Brick;


typedef struct
{
	float x, y, dx;
}Bullet;

typedef struct
{
	//scroll follow
	float scrollX;
	
	//Player
	Player player;
	
	//Bullet
	Bullet* bullets[MAX_BULLETS];

	//Position Bricks
	Brick bricks[NUM_PBRICK];

	//Position enemies
	Enemy *enemies[NUM_ENEMIES];


	//Renderer
	SDL_Renderer *renderer1;

	//Time
	int time;

	//Image
	SDL_Texture* IMGbrick;
	SDL_Texture* playerFrames[3];
	SDL_Texture* backGr;
	SDL_Texture* IMGenemies;
	SDL_Texture* IMGbullet;
	SDL_Texture* label;
	int label_w, label_h;


	//Status
	short status;
	
	//Fonts
	TTF_Font* font;
} GameState;

void loadGame(GameState* game);
int processEvent(SDL_Window* windown, GameState* game);
void addBullet(GameState* game);
short checkBulletsWithBrick(GameState* game, int j);
short checkBulletsWithEnemies(GameState* game, int j);
short checkBullets(GameState* game, int j);
void removeBullet(GameState* game, int i);
void removeEnemies(GameState* game, int i);
void processGameAni(GameState* game);
void collisionDetect(GameState* game);
short collision_with_ennemies(GameState* game);
void doRenderer(SDL_Renderer* renderer, GameState* game);


//screen status
void init_status_lives(GameState* game);
void draw_status_lives(GameState* game);
void shutdown_status_lives(GameState* game);