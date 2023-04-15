#pragma once
#include "audio.h"

Mix_Chunk* soundEffect[6];
Mix_Music* soundBackground[6];
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
    soundEffect[2] = Mix_LoadWAV("dame.wav");
    soundEffect[3] = Mix_LoadWAV("walking.wav");
    soundEffect[4] = Mix_LoadWAV("bossshot.wav");
    soundEffect[5] = Mix_LoadWAV("flash.wav");
    soundBackground[0] = Mix_LoadMUS("background.mp3");
    soundBackground[1] = Mix_LoadMUS("ED.mp3");
    soundBackground[2] = Mix_LoadMUS("OP.mp3");
    soundBackground[3] = Mix_LoadMUS("Boss.mp3");
    soundBackground[4] = Mix_LoadMUS("Win.mp3");



    if (soundEffect == NULL) {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    return 0;
}

void cleanUpAudio() 
{
    for (int i = 0; i <=5; i++)
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
    Mix_PlayChannel(0, soundEffect[0], 0, 0);
}

void shotSound() 
{
    // Phát âm thanh
    Mix_PlayChannel(1, soundEffect[1], 0);
}

void dameSound()
{
    // Phát âm thanh
    Mix_PlayChannel(2, soundEffect[2], 0);
}

void walkingSound()
{
    // Phát âm thanh
    Mix_PlayChannel(-1, soundEffect[3], 0);
}

void bossShot()
{
    Mix_PlayChannel(3, soundEffect[4], 0);
}

void flash()
{
    Mix_PlayChannel(4, soundEffect[5], 0);
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

void opMusic()
{
    // Phát âm thanh
    Mix_PlayMusic(soundBackground[2], -1);
}

void bossMusic()
{
    // Phát âm thanh
    Mix_PlayMusic(soundBackground[3], -1);
}

void winMusic()
{
    //Phát âm thanh
    Mix_PlayMusic(soundBackground[4], -1);

}