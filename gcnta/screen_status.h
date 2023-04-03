#pragma once
#include "libary.h"

void initStatusLives(GameState* game);
void initStatusOver(GameState* game);
void screenStart(SDL_Renderer* renderer, GameState* game);
void screenContain(SDL_Renderer* renderer, GameState* game);
void followScreen(GameState* game);
void scrennOver(SDL_Renderer* renderer, GameState* game);
void drawStatusLives(GameState* game);
void drawStatusOver(GameState* game);
void shutdownStatusLives(GameState* game);