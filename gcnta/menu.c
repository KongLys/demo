#include "menu.h"
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

short menuOP(SDL_Renderer* renderer, TTF_Font* font, short done)
{
    OPMusic();
    GameState gameState;
    MenuItem items[] = {
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 0, 0 }, "CONTINUE", { 255, 255, 155, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0 }, "NEW GAME", { 255, 255, 155, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, 0, 0 }, "LEAVE",    { 255, 255, 155, 255 } }
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
    SDL_RenderCopy(renderer, backGrText, NULL, &backGr);
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
                        
                        SDL_Quit();
                    }
                    if (selected_item == 1)
                    {
                        backgroundMusic();
                        done = 0;
                        quit = 1;
                    }
                    if (selected_item == 2)
                    {                        
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

                            SDL_Quit();
                        }
                        if (selected_item == 1)
                        {
                            backgroundMusic();
                            done = 0;
                            quit = 1;
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

short menuED(SDL_Renderer* renderer, TTF_Font* font, short done)
{
    endMusic();
    GameState gameState;
    MenuItem items[] = {
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 0, 0 }, "MENU", { 255, 255, 255, 255 } },
        { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, 0, 0 }, "LEAVE", { 255, 255, 255, 255 } }
    };
    short item_count = sizeof(items) / sizeof(items[2]);
    short selected_item = -1;

    //Load BackGround
    SDL_Surface* backGrSur;
    backGrSur = IMG_Load("menu_wallpaper.jpg");
    if (backGrSur == NULL)
    {
        printf("Cannot find menu_wallpaper.jpg! \n\n");
        SDL_Quit();
        exit(1);
    }
    SDL_Texture* backGrText = SDL_CreateTextureFromSurface(renderer, backGrSur);
    SDL_FreeSurface(backGrSur);
    SDL_Rect backGr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backGrText, NULL, &backGr);
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
                        done = 1;
                        menuOP(renderer, font, done);
                        quit = 1;
                    }
                    if (selected_item == 1)
                    {
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
                    if ((x >= items[i].rect.x - 50 && x <= items[i].rect.x + 50) && y >= items[i].rect.y - 32 && y <= items[i].rect.y + 32)
                    {
                        selected_item = i;
                        if (selected_item == 0)
                        {
                            done = 0;
                            menuOP(renderer, font, done);
                            quit = 1;
                        }
                        if (selected_item == 1)
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
}