#pragma once
#include "main_func.h"

void render_menu(SDL_Renderer* renderer, MenuItem* items, int item_count, int selected_item, TTF_Font* font);
void menu(SDL_Renderer* renderer, TTF_Font* font);