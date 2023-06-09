﻿#include "menu.h"
#include "audio.h"


void render_menu(SDL_Renderer* renderer, MenuItem* items, int item_count, int selected_item, TTF_Font* font) {

    for (int i = 0; i < item_count; i++) {
        SDL_Rect item_rect = items[i].rect;
        SDL_Color text_color = items[i].text_color;

        if (i == selected_item) {
            text_color.r = 255;
            text_color.g = 0;
            text_color.b = 255;
        }


        SDL_RenderFillRect(renderer, &item_rect);
        SDL_Color color = { 255, 255, 255 };
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, items[i].label, text_color);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_Rect text_rect = { item_rect.x + (item_rect.w - text_surface->w) / 2, item_rect.y + (item_rect.h - text_surface->h) / 2, text_surface->w, text_surface->h };
        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
    }

    SDL_RenderPresent(renderer);
}

void menuOP(SDL_Renderer* renderer, TTF_Font* font, GameState* game)
{
    opMusic();
    MenuItem items[] = {
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 0, 0 }, "CONTINUE", { 255, 255, 155, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0 }, "NEW GAME", { 255, 255, 155, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, 0, 0 }, "HOW TO PLAY", { 255, 255, 155, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, 0, 0 }, "LEAVE",    { 255, 255, 155, 255 } }
    };
    short item_count = sizeof(items) / sizeof(items[0]);
    short selected_item = -1;

    //Load BackGround
    SDL_Surface* backGrSur;
    backGrSur = IMG_Load("OP_screen.png");
    if (backGrSur == NULL)
    {
        printf("OP_screen! \n\n");
        SDL_Quit();
        exit(1);
    }
    SDL_Texture* backGrText = SDL_CreateTextureFromSurface(renderer, backGrSur);
    SDL_FreeSurface(backGrSur);
    SDL_Rect backGr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backGrText, NULL, &backGr);
    TTF_Font* fontSus = TTF_OpenFont("victor-pixel.ttf", 90);
    SDL_Color color = { 255, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Solid(fontSus, "SUS ADVENTURE", color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect SusRect = { SCREEN_WIDTH / 2 - 380 , SCREEN_HEIGHT / 2 - 250, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &SusRect);

    SDL_RenderPresent(renderer);
    render_menu(renderer, items, item_count, selected_item, font);


    SDL_Event event;
    short quit = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_w:
                case SDLK_UP:
                    selected_item = (selected_item - 1 + item_count) % item_count;
                    render_menu(renderer, items, item_count, selected_item, font);
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    selected_item = (selected_item + 1) % item_count;
                    render_menu(renderer, items, item_count, selected_item, font);
                    break;
                case SDLK_RETURN:
                {
                    if (selected_item == 0)
                    {
                        backgroundMusic();
                        game->continueGame = 1;
                        game->done = 0;
                        quit = 1;
                    }
                    if (selected_item == 1)
                    {
                        //player_name(renderer, font, &game);
                        backgroundMusic();
                        game->continueGame = 0;
                        game->done = 0;
                        quit = 1;
                    }
                    if (selected_item == 2)
                    {
                        game->done = 1;
                        gamePLay(renderer, font, game);
                        quit = 1;
                        
                    }
                    if (selected_item == 3)
                    {
                        game->done = 1;
                        
                        quit = 1;
                    }
                    break;
                }

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                for (int i = 0; i < item_count; i++)
                {
                    if ((x >= items[i].rect.x - 200 && x <= items[i].rect.x + 200) && y >= items[i].rect.y - 32 && y <= items[i].rect.y + 32)
                    {
                        selected_item = i;
                        if (selected_item == 0) 
                        {
                            game->done = 0;
                            game->continueGame = 1; 
                            quit = 1;
                        }
                        if (selected_item == 1)
                        {
                            //player_name(renderer, font, &game);
                            game->continueGame = 0;
                            game->done = 0;
                            quit = 1;
                        }
                        if (selected_item == 2)
                        {
                            game->done = 1;
                            gamePLay(renderer, font, game);
                            quit = 1;
                        }
                        if (selected_item == 3)
                        {
                            game->done = 1;
                            quit = 1;
                        }
                        break;
                    }
                }

                break;
            }
            case SDL_MOUSEMOTION:
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                for (int i = 0; i < item_count; i++)
                {
                    if ((x >= items[i].rect.x - 100 && x <= items[i].rect.x + 100) && y >= items[i].rect.y - 32 && y <= items[i].rect.y + 32)
                    {
                        selected_item = i;
                        render_menu(renderer, items, item_count, selected_item, font);
                    }
                }
                break;
            }
            break;
            }
        }
    }
}

void menuED(SDL_Renderer* renderer, TTF_Font* font, GameState* game, SDL_Window* windown)
{
    endMusic();
    char* score = (char*)malloc(30 * sizeof(char));
    sprintf_s(score, 30, "Score: %d", game->player.score);
    MenuItem items[] = {
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0 }, "PLAY AGAIN", { 255, 255, 255, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, 0, 0 }, "LEAVE", { 255, 255, 255, 255 } }
    };
    MenuItem over[] = {
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200, 0, 0 }, "GAMEOVER DUDEEE!", { 255, 0, 0, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 0, 0 }, score , { 255, 0, 0, 255 } }
    };
    short item_count = sizeof(items) / sizeof(items[2]);
    short selected_item = -1;
    //Load BackGround
    SDL_Surface* backGrSur;
    backGrSur = IMG_Load("losegame.png");
    if (backGrSur == NULL)
    {
        printf("losegame.png! \n\n");
        SDL_Quit();
        exit(1);
    }
    SDL_Texture* backGrText = SDL_CreateTextureFromSurface(renderer, backGrSur);
    SDL_FreeSurface(backGrSur);
    SDL_Rect backGr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backGrText, NULL, &backGr);
    SDL_RenderPresent(renderer);

    render_menu(renderer, items, item_count, selected_item, font);
    render_menu(renderer, over, 2, -2, font);

    SDL_Event event;
    short quit = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_w:
                    case SDLK_UP:
                        selected_item = (selected_item - 1 + item_count) % item_count;
                        render_menu(renderer, items, item_count, selected_item, font);
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        selected_item = (selected_item + 1) % item_count;
                        render_menu(renderer, items, item_count, selected_item, font);
                        break;
                    case SDLK_RETURN:
                    {
                        if (selected_item == 0)
                        {
                            backgroundMusic();   
                            game->player.score = 0;
                            game->player.x = 250;
                            game->player.y = 10;
                            game->player.lives = 3;
                            save_process(game);
                            loadAgain(game);
                            quit = 1;
                        }
                        if (selected_item == 1)
                        {
                            
                            game->player.score = 0;
                            game->player.x = 250;
                            game->player.y = 10;
                            game->player.lives = 3;
                            save_process(game);
                            quit = 1;
                            game->done = 1;
                        }
                        break;     
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                for (int i = 0; i < item_count; i++)
                {
                    if ((x >= items[i].rect.x - 150 && x <= items[i].rect.x + 150) && y >= items[i].rect.y - 32 && y <= items[i].rect.y + 32)
                    {
                        selected_item = i;
                        if (selected_item == 0)
                        {
                            backgroundMusic(); 
                         
                            game->player.score = 0;
                            game->player.x = 250;
                            game->player.y = 10;
                            game->player.lives = 3;
                            save_process(game);
                            loadAgain(game); 
                            quit = 1;
                        }
                        if (selected_item == 1)
                        {
                            game->player.score = 0;
                            game->player.x = 250;
                            game->player.y = 10;
                            game->player.lives = 3;
                            save_process(game);
                            quit = 1;
                            game->done = 1;
                        }
                        break;
                    }
                }

                break;
            }
            case SDL_MOUSEMOTION:
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                for (int i = 0; i < item_count; i++)
                {
                    if ((x >= items[i].rect.x - 55 && x <= items[i].rect.x + 55) && y >= items[i].rect.y - 32 && y <= items[i].rect.y + 32)
                    {
                        selected_item = i;
                        render_menu(renderer, items, item_count, selected_item, font);
                    }
                }
                break;
            }
            break;
            }
        }
    }   
    free(score);
}

void menuWin(SDL_Renderer* renderer, TTF_Font* font, GameState* game)
{
    winMusic();
    char* score = (char*)malloc(30 * sizeof(char));
    sprintf_s(score, 30, "Score: %d", game->player.score);
    MenuItem items[] = {
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 0, 0 }, "YOU WIN", { 255, 0, 0, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, 0, 0 }, "QUIT", { 255, 255, 155, 255 } }
    };
    MenuItem winScore[] = { { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0 }, score , { 255, 0, 0, 255 } } };
    short item_count = sizeof(items) / sizeof(items[0]);
    short selected_item = -1;
    


    //Load BackGround
    SDL_Surface* backGrSur;
    backGrSur = IMG_Load("wingame.png");
    if (backGrSur == NULL)
    {
        printf("wingame.png! \n\n");
        SDL_Quit();
        exit(1);
    }
    SDL_Texture* backGrText = SDL_CreateTextureFromSurface(renderer, backGrSur);
    SDL_FreeSurface(backGrSur);
    SDL_Rect backGr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backGrText, NULL, &backGr);
    SDL_RenderPresent(renderer);

    render_menu(renderer, items, item_count, selected_item, font);
    render_menu(renderer, winScore, 1, -2, font);


    SDL_Event event;
    short quit = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_w:
                case SDLK_UP:
                    selected_item = 1;
                    render_menu(renderer, items, item_count, selected_item, font);
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    selected_item = 1;
                    render_menu(renderer, items, item_count, selected_item, font);
                    break;
                case SDLK_RETURN:
                {
                    if (selected_item == 1)
                    {
                        game->done = 1;
                        quit = 1;
                    }
                    break;
                }

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                for (int i = 1; i < item_count; i++)
                {
                    if ((x >= items[i].rect.x - 100 && x <= items[i].rect.x + 100) && y >= items[i].rect.y - 32 && y <= items[i].rect.y + 32)
                    {
                        selected_item = i;
                        if (selected_item == 1)
                        {
                            game->done = 1;
                            quit = 1;
                        }
                        break;
                    }
                }

                break;
            }
            case SDL_MOUSEMOTION:
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                for (int i = 1; i < item_count; i++)
                {
                    if ((x >= items[i].rect.x - 100 && x <= items[i].rect.x + 100) && y >= items[i].rect.y - 32 && y <= items[i].rect.y + 32)
                    {
                        selected_item = i;
                        render_menu(renderer, items, item_count, selected_item, font);
                    }
                }
                break;
            }
            break;
            }
        }
    }
}

void gamePLay(SDL_Renderer* renderer, TTF_Font* font, GameState* game)
{
    SDL_RenderClear(renderer);
    MenuItem items[] = {
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 350, 0, 0 }, "Z, L: Dash", { 255, 255, 255, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 250, 0, 0 }, "X, K: Jump", { 255, 255, 255, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150, 0, 0 }, "C, J: Fire",    { 255, 255, 255, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 0, 0 }, "W, UP BUTTON: Fire Up", { 255, 255, 255, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, 0, 0 }, "S, DOWN BUTTON: Fire Down", { 255, 255, 255, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 150, 0, 0 }, "A: Move left", { 255, 255, 255, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 250, 0, 0 }, "D: Move right", { 255, 255, 255, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 350, 0, 0 }, "BACK",{ 255, 255, 255, 255 } }
    };
    short item_count = sizeof(items) / sizeof(items[0]);
    short selected_item = -1;

    render_menu(renderer, items, item_count, selected_item, font);

    SDL_Event event;
    short quit = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_w:
                case SDLK_UP:
                    selected_item = (selected_item - 1 + item_count) % item_count;
                    render_menu(renderer, items, item_count, selected_item, font);
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    selected_item = (selected_item + 1) % item_count;
                    render_menu(renderer, items, item_count, selected_item, font);
                    break;
                case SDLK_RETURN:
                {
                    if (selected_item == 7)
                    {
                        game->done = 0;
                        quit = 1;
                        menuOP(renderer, font, game);
                    }

                    break;
                }

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                for (int i = 0; i < item_count; i++)
                {
                    if ((x >= items[i].rect.x - 100 && x <= items[i].rect.x + 100) && y >= items[i].rect.y - 32 && y <= items[i].rect.y + 32)
                    {
                        selected_item = i;
                        if (selected_item == 7)
                        {
                            game->done = 0;
                            quit = 1;
                            menuOP(renderer, font, game);
                        }
                        break;
                    }
                }

                break;
            }
            case SDL_MOUSEMOTION:
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                for (int i = 0; i < item_count; i++)
                {
                    if ((x >= items[i].rect.x - 100 && x <= items[i].rect.x + 100) && y >= items[i].rect.y - 32 && y <= items[i].rect.y + 32)
                    {
                        selected_item = i;
                        render_menu(renderer, items, item_count, selected_item, font);
                    }
                }
                break;
            }
            break;
            }
        }
    }
}
// How to play ?
void menuPause(SDL_Renderer* renderer, TTF_Font* font)
{
    MenuItem items[] = {
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 0, 0 }, "CONTINUE", { 255, 255, 255, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0 }, "SETTING", { 255, 255, 255, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, 0, 0 }, "LEAVE",    { 255, 255, 255, 255 } }
    };
    short item_count = sizeof(items) / sizeof(items[0]);
    short selected_item = -1;

    render_menu(renderer, items, item_count, selected_item, font);

    SDL_Event event;
    short quit = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_w:
                case SDLK_UP:
                    selected_item = (selected_item - 1 + item_count) % item_count;
                    render_menu(renderer, items, item_count, selected_item, font);
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    selected_item = (selected_item + 1) % item_count;
                    render_menu(renderer, items, item_count, selected_item, font);
                    break;
                case SDLK_RETURN:
                {
                    if (selected_item == 0)
                    {
                        quit = 1;
                    }
                    if (selected_item == 1)
                    {
                        quit = 1;
                        SDL_Quit();
                    }
                    if (selected_item == 2)
                    {
                        quit = 1;
                        SDL_Quit();
                    }

                    break;
                }

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                for (int i = 0; i < item_count; i++)
                {
                    if ((x >= items[i].rect.x - 100 && x <= items[i].rect.x + 100) && y >= items[i].rect.y - 32 && y <= items[i].rect.y + 32)
                    {
                        selected_item = i;
                        if (selected_item == 0)
                        {
                            quit = 1;
                        }
                        if (selected_item == 1)
                        {
                            quit = 1;
                            SDL_Quit();
                        }
                        if (selected_item == 2)
                        {
                            SDL_Quit();
                        }
                        break;
                    }
                }

                break;
            }
            case SDL_MOUSEMOTION:
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                for (int i = 0; i < item_count; i++)
                {
                    if ((x >= items[i].rect.x - 100 && x <= items[i].rect.x + 100) && y >= items[i].rect.y - 32 && y <= items[i].rect.y + 32)
                    {
                        selected_item = i;
                        render_menu(renderer, items, item_count, selected_item, font);
                    }
                }
                break;
            }
            break;
            }
        }
    }
}
/*
char* player_name(SDL_Renderer* renderer, TTF_Font* font, GameState* game)
{
    MenuItem items[] = {
        { { SCREEN_WIDTH / 2 - 170, SCREEN_HEIGHT / 2, 0, 0 }, "YOUR NAME:", { 255, 255, 155, 255 } }
    };
    short item_count = sizeof(items) / sizeof(items[0]);
    short selected_item = -1;

    //Load BackGround
    SDL_Surface* backGrSur;
    backGrSur = IMG_Load("menuOP_wallpaper.jpg");
    if (backGrSur == NULL)
    {
        printf("Cannot find menuOP_wallpaper.jpg! \n\n");
        SDL_Quit();
        exit(1);
    }
    SDL_Texture* backGrText = SDL_CreateTextureFromSurface(renderer, backGrSur);
    SDL_FreeSurface(backGrSur);
    SDL_Rect backGr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    // bắt kí  tự nhập chuỗi (1)
    char inputText[100] = "";
    int len = 0;
    
    //game->player.name = (char*)malloc(50 * sizeof(char));

    SDL_Color textColor = { 255, 255, 255, 255 };
    // xử lí sự kiện
    short quit = 0;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_BACKSPACE && len > 0) {
                    // Xóa ký tự cuối cùng
                    inputText[len - 1] = '\0';
                    len--;
                }
                if (event.key.keysym.sym == SDLK_RETURN && len > 0) {
                    game->player.name = inputText;
                    quit = 1;
                }
                break;
            case SDL_TEXTINPUT:
                // Thêm ký tự mới vào cuối chuỗi
                strcat(inputText, event.text.text);
                len++;
                break;
            }
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, backGrText, NULL, &backGr);
            // truyền -1 vào để trong render_menu không làm đổi màu khi ta bấm nút
            render_menu(renderer, items, item_count, -1, font);
            int x = SCREEN_WIDTH / 2, y = SCREEN_HEIGHT / 2 - 25;
            for (int i = 0; i < len; i++) {
                char c = inputText[i];

                // Vẽ kí tự
                SDL_Surface* surface = TTF_RenderGlyph_Blended(font, c, textColor);
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_Rect destRect = { x, y, surface->w, surface->h };
                SDL_RenderCopy(renderer, texture, NULL, &destRect);


                // Tăng x để chuẩn bị vẽ kí tự tiếp theo
                x += destRect.w;
            }

            SDL_RenderPresent(renderer);
        }
    }
    return inputText;
    free(inputText);
}
*/