#ifndef CHOOSECHESSPROMOTE_HPP
#define CHOOSECHESSPROMOTE_HPP
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
using namespace std;
int x = 0, y = 0;
int choose() {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Choose", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 300, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* surface = IMG_Load("images/covua.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    int x = 0, y = 0;
    bool quit = false;
    while (!quit)
        {
         while (SDL_PollEvent(&event) != 0)
          {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                x = event.button.x;
                y = event.button.y;
                quit = true;
                break;
            }
         }
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    if (x < 100)
        return 4;
    if (x >= 100 && x <= 200)
        return 3;
    if (x >= 200 && x <= 300)
        return 2;
    return 1;
}
#endif
