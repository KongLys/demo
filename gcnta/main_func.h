#pragma once

#include "libary.h"
#include "screen_status.h"
#include "load_game.h"
#include "enemies.h"
#include "bullet.h"
#include "collision.h"
#include "menu.h"

int processEvent(SDL_Window* windown, GameState* game);
void processGame(GameState* game);
void doRenderer(SDL_Renderer* renderer, GameState* game);
