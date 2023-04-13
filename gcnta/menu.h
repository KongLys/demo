#pragma once
#include "main_func.h"

void render_menu(SDL_Renderer* renderer, MenuItem* items, int item_count, int selected_item, TTF_Font* font);
void menuOP(SDL_Renderer* renderer, TTF_Font* font , GameState* game);
void menuED(SDL_Renderer* renderer, TTF_Font* font, GameState* game);
void menuWin(SDL_Renderer* renderer, TTF_Font* font, GameState* game);
//char* player_name(SDL_Renderer* renderer, TTF_Font* font);
void menuPause(SDL_Renderer* renderer, TTF_Font* font);