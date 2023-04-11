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
			if (val != 0)
			{
				cnt++;
			}
		}
	}
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
				game->enemies[cnt]->x = j * game->enemies[cnt]->w;
				game->enemies[cnt]->y = i * game->enemies[cnt]->h;
				game->enemies[cnt]->flipChar = 1;
				game->enemies[cnt]->dx = 2;
				game->enemies[cnt]->dy = 2;
				game->enemies[cnt]->lives = 2;
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
				game->enemiesShort[cnt]->x = j * game->enemiesShort[cnt]->w;
				game->enemiesShort[cnt]->y = i * game->enemiesShort[cnt]->h;
				game->enemiesShort[cnt]->xAni = 0;
				game->enemiesShort[cnt]->yAni = 1;
				game->enemiesShort[cnt]->dx = 2;
				game->enemiesShort[cnt]->dy = 2;
				game->enemiesShort[cnt]->valid = 1;
				game->enemiesShort[cnt]->flipChar = 1;
				game->enemiesShort[cnt]->lives = 1;
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