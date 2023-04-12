#pragma once
#include "audio.h"

Mix_Chunk* soundEffect[3];
Mix_Music* soundBackground[3];
Mix_Chunk* jumpEffect;
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
    jumpEffect = Mix_LoadWAV("jump.wav");
    soundEffect[0] = Mix_LoadWAV("hit.wav");
    soundEffect[1] = Mix_LoadWAV("dame.wav");
    soundEffect[2] = Mix_LoadWAV("walking.wav");
    soundBackground[0] = Mix_LoadMUS("background.mp3");
    soundBackground[1] = Mix_LoadMUS("rat.mp3");
    soundBackground[2] = Mix_LoadMUS("OP.mp3");


    if (soundEffect == NULL) {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    return 0;
}

void cleanUpAudio() 
{
    Mix_FreeChunk(jumpEffect);
    for (int i = 0; i < 3; i++)
    {
        Mix_FreeMusic(soundBackground[i]);
        Mix_FreeChunk(soundEffect[i]);
    }
    Mix_CloseAudio();
    SDL_Quit();
}

void jumbSound() 
{
    // Phát âm thanh
    Mix_PlayChannelTimed (-1, jumpEffect, 0, 0);
}

void shotSound() 
{
    // Phát âm thanh
    Mix_PlayChannel(-1, soundEffect[0], 0);
}

void dameSound()
{
    // Phát âm thanh
    Mix_PlayChannel(-1, soundEffect[1], 0);
}

void walkingSound()
{
    // Phát âm thanh
    Mix_PlayChannel(-1,  soundEffect[2], 0);
}

void backgroundMusic()
{
    // Phát âm thanh
    Mix_PlayMusic(soundBackground[0], -1);
}

void endMusic()
{
    // Phát âm thanh
    Mix_PlayMusic(soundBackground[1], -1);
}

void OPMusic()
{
    // Phát âm thanh
    Mix_PlayMusic(soundBackground[2], -1);
}
