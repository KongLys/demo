#pragma once
#include "audio.h"

Mix_Chunk* soundEffect[2];
Mix_Music* soundBackground;

int initAudio() 
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    // Load file âm thanh
    soundEffect[0] = Mix_LoadWAV("jump.wav");
    soundEffect[1] = Mix_LoadWAV("hit.wav");
    soundBackground = Mix_LoadMUS("background.mp3");

    if (soundEffect == NULL) {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    return 0;
}

void cleanUpAudio() 
{
    Mix_FreeChunk(soundEffect);
    Mix_CloseAudio();
    SDL_Quit();
}

void jumbSound() 
{
    // Phát âm thanh
    Mix_PlayChannel(-1, soundEffect[0], 0);
}
void shotSound() 
{
    // Phát âm thanh
    Mix_PlayChannel(-1, soundEffect[1], 0);

}
void backgroundMusic()
{
    // Phát âm thanh
    Mix_PlayMusic(soundBackground, -1);

}
