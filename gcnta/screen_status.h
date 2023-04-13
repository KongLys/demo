#pragma once
#include "libary.h"

void initStatusLives(GameState* game);
void screenStart(SDL_Renderer* renderer, GameState* game);
void screenContain(SDL_Renderer* renderer, GameState* game);
void followScreen(GameState* game);
void drawStatusLives(GameState* game);
void shutdownStatusLives(GameState* game);