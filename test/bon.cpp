#include <SDL.h>
#include "SDL2ImageRenderer.hpp"

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL2ImageRenderer imageRenderer(renderer);
    std::string imagePath[2] = {"images/figures.png", "images/board.png"};
    int i = 0;
    while(true)
    {
    imageRenderer.loadImage(imagePath[i]);
    imageRenderer.renderImage(100, 100);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    i++;
    }
     SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
