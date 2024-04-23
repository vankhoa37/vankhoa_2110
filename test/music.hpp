#ifndef MUSIC_H
#define MUSIC_H
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

void playVictoryMusic() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *music = Mix_LoadMUS("victory_music.mp3");
    if (!music) {
        std::cerr << "Error loading victory music: " << Mix_GetError() << std::endl;
        return;
    }
    Mix_PlayMusic(music, 1);
}

void playErrorMusic() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *music1 = Mix_LoadMUS("error_music.mp3");
    if (!music1) {
        std::cerr << "Error loading error music: " << Mix_GetError() << std::endl;
        return;
    }
    Mix_PlayMusic(music1, 1);
}

void playCorrectMusic() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *music2 = Mix_LoadMUS("correct_music.mp3");
    if (!music2) {
        std::cerr << "Error loading correct music: " << Mix_GetError() << std::endl;
        return;
    }
    std:: cout << "loading" << std::endl;
    Mix_PlayMusic(music2, 1);
}

void playMusic() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *music3 = Mix_LoadMUS("music.mp3");
    if (!music3) {
        std::cerr << "Error loading music: " << Mix_GetError() << std::endl;
        return;
    }

    Mix_PlayMusic(music3, 1);
}

void playMoveMusic() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *music4 = Mix_LoadMUS("dichuyenquanco.mp3");
    if (!music4) {
        std::cerr << "Error loading move music: " << Mix_GetError() << std::endl;
        return;
    }
    Mix_PlayMusic(music4, 1);
}

#endif
