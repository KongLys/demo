#pragma once

#include <stdio.h>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT  768 
#define NUM_PBRICK 100
#define NUM_ENEMIES 50
#define NUM_ENEMIES_2 50
#define MAX_BULLETS 25
#define MAX_BULLETS_ENEMIES 75
#define MAX_MENUITEMS 4

#define GRAVITY 0.4

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
	float dx, dy;
	short animFrame, flipChar, onBrick, shootBullet;
	short lives;
} Enemy;

typedef struct
{
	float  x, y, w, h;
	float dx, dy;
	short flipChar;
	short lives, valid;
	int xAni, yAni;
} EnemyShort;

typedef struct
{
	float x, y, w, h;
} Brick;


typedef struct
{
	float x, y, dx, dy;
	float rangeLeft, rangeRight;
}Bullet;

typedef struct {
	SDL_Rect rect;
	const char* label;
	SDL_Color text_color;
} MenuItem;


typedef struct
{
	//scroll follow
	float scrollX;

	//Player
	Player player;

	//Bullet
	Bullet* bullets[MAX_BULLETS];
	Bullet* bulletEnemies[MAX_BULLETS_ENEMIES];

	//Position Bricks
	Brick bricks[NUM_PBRICK];

	//Position enemies
	Enemy* enemies[NUM_ENEMIES];
	EnemyShort* enemiesShort[NUM_ENEMIES_2];

	//Menu Items
	MenuItem* items;

	//Renderer
	SDL_Renderer* renderer1;

	//Time
	int time;

	//Image
	SDL_Texture* IMGbrick;
	SDL_Texture* playerFrames[3];
	SDL_Texture* backGr;
	SDL_Texture* IMGenemies;
	SDL_Texture* IMGenemiesShort;
	SDL_Texture* IMGbullet;
	SDL_Texture* label;
	SDL_Surface* backGrSur;

	int label_w, label_h;


	//Status
	short status;

	//Fonts
	TTF_Font* font;
} GameState;