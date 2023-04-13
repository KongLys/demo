#pragma once
#include "libary.h"
#include "map.h"

void loadGame(GameState* game);
void loadAgain(GameState* game);
void save_process(GameState* game);
short take_process(GameState* game);
short readXY(GameState* game);
