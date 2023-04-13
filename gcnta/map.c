#include "map.h"

int cntEnemies(GameState* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "map_demo.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open map_demo.txt!\n\n");
		return;
	}
	int cnt = 0;
	for (int i = 0, val = 0; i < MAX_Y; i++)
	{
		for (int j = 0; j < MAX_X; j++)
		{
			fscanf_s(fp, "%d", &val);
			if (val == 2)
			{
				cnt++;
			}
		}
	}
	game->enemies = (Enemy**)malloc(cnt * sizeof(Enemy*));
	fclose(fp);
	return cnt;
}

int cntEnemiesShort(GameState* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "map_demo.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open map_demo.txt!\n\n");
		return;
	}
	int cnt = 0;
	for (int i = 0, val = 0; i < MAX_Y; i++)
	{
		for (int j = 0; j < MAX_X; j++)
		{
			fscanf_s(fp, "%d", &val);
			if (val == 3)
			{
				cnt++;
			}
		}
	}
	game->enemiesShort = (EnemyShort**)malloc(cnt * sizeof(EnemyShort*));
	fclose(fp);
	return cnt;
}

int cntBoss(GameState* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "map_demo.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open map_demo.txt!\n\n");
		return;
	}
	int cnt = 0;
	for (int i = 0, val = 0; i < MAX_Y; i++)
	{
		for (int j = 0; j < MAX_X; j++)
		{
			fscanf_s(fp, "%d", &val);
			if (val == 6)
			{
				cnt++;
			}
		}
	}
	game->boss = (Boss**)malloc(cnt * sizeof(Boss*));
	fclose(fp);
	return cnt;
}

int cntCheckPoint(GameState* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "map_demo.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open map_demo.txt!\n\n");
		return;
	}
	int cnt = 0;
	for (int i = 0, val = 0; i < MAX_Y; i++)
	{
		for (int j = 0; j < MAX_X; j++)
		{
			fscanf_s(fp, "%d", &val);
			if (val == 5)
			{
				cnt++;
			}
		}
	}
	game->checkpoint = (CheckPoint**)malloc(cnt * sizeof(CheckPoint*));
	fclose(fp);
	return cnt;
}

int cntBrick(GameState* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "map_demo.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open map_demo.txt!\n\n");
		return;
	}
	int cnt = 0;
	for (int i = 0, val = 0; i < MAX_Y; i++)
	{
		for (int j = 0; j < MAX_X; j++)
		{
			fscanf_s(fp, "%d", &val);
			if (val == 1)
			{
				cnt++;
			}
		}
	}
	fclose(fp);
	return cnt;
}

int cntCoin(GameState* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "map_demo.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open map_demo.txt!\n\n");
		return;
	}
	int cnt = 0;
	for (int i = 0, val = 0; i < MAX_Y; i++)
	{
		for (int j = 0; j < MAX_X; j++)
		{
			fscanf_s(fp, "%d", &val);
			if (val == 4)
			{
				cnt++;
			}
		}
	}
	game->coin = (Coin**)malloc(cnt * sizeof(Coin*));
	fclose(fp);
	return cnt;
}

void loadEnemies(GameState* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "map_demo.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open map_demo.txt!\n\n");
		return;
	}
	for (int i = 0; i < game->numEnemies; i++)
	{
		game->enemies[i] = (Enemy*)malloc(sizeof(Enemy));
	}
	for (int i = 0, cnt = 0, val = 0; i < MAX_Y; i++)
	{
		for (int j = 0; j < MAX_X; j++)
		{
			fscanf_s(fp, "%d", &val);
			if (val == 2)
			{

				game->enemies[cnt]->w = 64;
				game->enemies[cnt]->h = 64;
				game->enemies[cnt]->x = j * 120;
				game->enemies[cnt]->y = i * 60;
				game->enemies[cnt]->flipChar = 1;
				game->enemies[cnt]->dx = 2;
				game->enemies[cnt]->dy = 2;
				game->enemies[cnt]->lives = 2;
				if (game->enemies[cnt]->x <= game->player.x)
				{
					free(game->enemies[cnt]);
					game->enemies[cnt] = NULL;
				}	
				cnt++;
			}
			
		}
	}
	fclose(fp);
}

void loadEnemiesShort(GameState* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "map_demo.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open map_demo.txt!\n\n");
		return;
	}
	for (int i = 0; i < game->numEnemiesShort; i++)
	{
		game->enemiesShort[i] = (EnemyShort*)malloc(sizeof(EnemyShort));
	}
	for (int i = 0, cnt = 0, val = 0; i < MAX_Y; i++)
	{
		for (int j = 0; j < MAX_X; j++)
		{
			fscanf_s(fp, "%d", &val);
			if (val == 3)
			{
				game->enemiesShort[cnt]->w = 48;
				game->enemiesShort[cnt]->h = 48;
				game->enemiesShort[cnt]->x = j * 120 + 60;
				game->enemiesShort[cnt]->y = i * 60;
				game->enemiesShort[cnt]->xAni = 0;
				game->enemiesShort[cnt]->yAni = 1;
				game->enemiesShort[cnt]->dx = 2;
				game->enemiesShort[cnt]->dy = 2;
				game->enemiesShort[cnt]->valid = 1;
				game->enemiesShort[cnt]->flipChar = 1;
				game->enemiesShort[cnt]->lives = 1;	
				if (game->enemiesShort[cnt]->x <= game->player.x)
				{
					free(game->enemiesShort[cnt]);
					game->enemiesShort[cnt] = NULL;
				}
				cnt++;
			}		
		}
	}
	fclose(fp);
}

void loadBoss(GameState* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "map_demo.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open map_demo.txt!\n\n");
		return;
	}
	for (int i = 0; i < game->numBoss; i++)
	{
		game->boss[i] = (Boss*)malloc(sizeof(Boss));
	}
	for (int i = 0, cnt = 0, val = 0; i < MAX_Y; i++)
	{
		for (int j = 0; j < MAX_X; j++)
		{
			fscanf_s(fp, "%d", &val);
			if (val == 6)
			{
				game->boss[cnt]->w = 360;
				game->boss[cnt]->h = 380;
				game->boss[cnt]->x = j * 120;
				game->boss[cnt]->y = i * 60;
				game->boss[cnt]->dx = 0;
				game->boss[cnt]->dy = 0;
				game->boss[cnt]->xAni = 0;
				game->boss[cnt]->flipChar = 0;
				game->boss[cnt]->lives = 1;
				cnt++;
			}
		}
	}
	fclose(fp);
}

void loadCoin(GameState* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "map_demo.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open map_demo.txt!\n\n");
		return;
	}
	for (int i = 0; i < game->numCoin; i++)
	{
		game->coin[i] = (Coin*)malloc(sizeof(Coin));
	}
	for (int i = 0, cnt = 0, val = 0; i < MAX_Y; i++)
	{
		for (int j = 0; j < MAX_X; j++)
		{
			fscanf_s(fp, "%d", &val);
			if (val == 4)
			{
				game->coin[cnt]->w = 24;
				game->coin[cnt]->h = 24;
				game->coin[cnt]->xAni = 0;
				game->coin[cnt]->yAni = 0;
				game->coin[cnt]->x = j * 120;
				game->coin[cnt]->y = i * 60 + 30;
				if (game->coin[cnt]->x <= game->player.x)
				{
					free(game->coin[cnt]);
					game->coin[cnt] = NULL;
				}
				cnt++;
			}
		}
	}
	fclose(fp);
}

void loadCheckPoint(GameState* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "map_demo.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open map_demo.txt!\n\n");
		return;
	}
	for (int i = 0; i < game->numCheckPoint; i++)
	{
		game->checkpoint[i] = (CheckPoint*)malloc(sizeof(CheckPoint));
	}
	for (int i = 0, cnt = 0, val = 0; i < MAX_Y; i++)
	{
		for (int j = 0; j < MAX_X; j++)
		{
			fscanf_s(fp, "%d", &val);
			if (val == 5)
			{ 
				game->checkpoint[cnt]->w = 20;
				game->checkpoint[cnt]->h = 50;
				game->checkpoint[cnt]->x = j * 120;
				game->checkpoint[cnt]->y = i * 60 + 10;
				game->checkpoint[cnt]->valid = 1;
				cnt++;
			}
		}
	}
	fclose(fp);
}

void loadMap(GameState* game)
{
	FILE* fp = NULL;
	fopen_s(&fp, "map_demo.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open map_demo.txt!\n\n");
		return;
	}
	game->bricks = (Brick**)malloc(game->numBrick * sizeof(Brick*));
	for (int i = 0; i < game->numBrick; i++)
	{
		game->bricks[i] = (Brick*)malloc(sizeof(Brick));
	}
	for (int i = 0, cnt = 0,val = 0; i < MAX_Y; i++)
	{
		for (int j = 0; j < MAX_X; j++)
		{
			fscanf_s(fp, "%d", &val);
			if (val == 1)
			{
				game->bricks[cnt]->w = 120;
				game->bricks[cnt]->h = 60;
				game->bricks[cnt]->x = j * game->bricks[cnt]->w;
				game->bricks[cnt]->y = i * game->bricks[cnt]->h;
				cnt++;
			}
		}
	}
	fclose(fp);
}