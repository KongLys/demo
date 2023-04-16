#pragma once

#include <stdio.h>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT  900
#define MAX_BULLETS 2
#define MAX_BULLETS_ENEMIES 75
#define MAX_BULLETS_BOSS 100
#define MAX_MENUITEMS 4

#define GRAVITY 0.5

#define GAME_NEW 0
#define GAME_PLAY 1
#define GAME_WIN 2



typedef struct
{
	float  x, y, w, h;
	float dx, dy;
	short flipChar, onBrick, stopMove, shootBullet, dashCoolDown, dashPower, canDash;
	short lives, hit, xAni, yAni, aiming, angle;
	int score;
} Player;
typedef struct
{
	float  x, y, w, h;
	float dx, dy;
	short flipChar;
	short lives;
	short killed;
} Enemy;

typedef struct
{
	float  x, y, w, h;
	float dx, dy;
	short flipChar;
	short lives, valid;
	short xAni, yAni;
	short killed;
} EnemyShort;

typedef struct
{
	float  x, y, w, h, dx, dy;
	short lives, xAni, flipChar;
} Boss;

typedef struct
{
	float  x, y, w, h, valid;
}CheckPoint;

typedef struct
{
	float x, y, w, h;
} Brick;

typedef struct
{
	float x, y, w, h;
	short xAni, yAni;
} Coin;

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
	Bullet* bulletBoss[MAX_BULLETS_BOSS];

	//Position Bricks
	Brick** bricks;
	int numBrick;

	//Position enemies
	Enemy** enemies;
	int numEnemies;
	EnemyShort** enemiesShort;
	int numEnemiesShort;

	//Position boss
	Boss** boss;
	int numBoss;

	//Coin
	Coin** coin;
	int numCoin;

	//CheckPoint
	CheckPoint** checkpoint;
	int numCheckPoint;

	//Menu Items
	MenuItem* items;

	//Renderer
	SDL_Renderer* renderer1;

	//Time
	int time;

	//Image
	SDL_Texture* IMGcheckpoint;
	SDL_Texture* IMGbrick;
	SDL_Texture* IMGPlayer;
	SDL_Texture* backGr;
	SDL_Texture* IMGCoin;
	SDL_Texture* IMGenemies;
	SDL_Texture* IMGenemiesShort;
	SDL_Texture* IMGbullet;
	SDL_Texture* IMGBoss;
	SDL_Texture* label;
	SDL_Surface* backGrSur;

	int label_w, label_h;

	//Continue
	short continueGame;

	//Status
	short status;

	//Fonts
	TTF_Font* font;

	//Condition to loopgame
	short done;

} GameState;
