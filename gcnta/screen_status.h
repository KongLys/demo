#pragma once
#include "libary.h"

void initStatusLives(GameState* game);
void initStatusOver(GameState* game);
void screenStart(SDL_Renderer* renderer, GameState* game);
void screenContain(SDL_Renderer* renderer, GameState* game);
void followScreen(GameState* game);
void screnWin(SDL_Renderer* renderer, GameState* game);
void drawStatusLives(GameState* game);
void drawStatusWin(GameState* game);
void shutdownStatusLives(GameState* game);