#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include "SDL2ImageRenderer.hpp"
#include "chess_game_1vs1.cpp"
#include "chess_game_nguoi_voi_may.cpp"
using namespace std;

const int WINDOW_WIDTH = 1368;
const int WINDOW_HEIGHT = 707;
bool create = false;
bool windowDestroyed = false;
vector<string> imagePaths = {"images/menugame1_1.jpg", "images/menugame1_2.jpg", "images/menugamechess2.jpg"};
int currentImageIndex = 0;

SDL_Window* window2 = nullptr;
SDL_Renderer* renderer2 = nullptr;
SDL2ImageRenderer imageRenderer(nullptr);

int main(int argc, char* args[]) {
    bool quit2 = false;
    int X, Y;

    SDL_Init(SDL_INIT_EVERYTHING);
    window2 = SDL_CreateWindow("Image Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer2 = SDL_CreateRenderer(window2, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  imageRenderer.setRenderer(renderer2);

    while (!quit2) {
        if (!create) {
            imageRenderer.loadImage(imagePaths[currentImageIndex]);
            SDL_RenderClear(renderer2);
            imageRenderer.renderImage(0, 0);
            SDL_RenderPresent(renderer2);
        }
        else if (create && !windowDestroyed) {
            SDL_DestroyWindow(window2);
            SDL_DestroyRenderer(renderer2);
            window2 = SDL_CreateWindow("Image Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
            renderer2 = SDL_CreateRenderer(window2, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            imageRenderer.setRenderer(renderer2);
            imageRenderer.loadImage(imagePaths[currentImageIndex]);
            SDL_RenderClear(renderer2);
            imageRenderer.renderImage(0, 0);
            SDL_RenderPresent(renderer2);
            create = false;
        }
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit2 = true;
            } else if (!windowDestroyed && e.type == SDL_MOUSEBUTTONDOWN) {
                X = e.button.x;
                Y = e.button.y;
                cout << X << " " << Y << endl;
                 if (X >= 254 && X <= 546 && Y >= 390 && Y <= 465 && currentImageIndex == 0) currentImageIndex = 2;
                 else if (X >= 1287 && X <= 1346 && Y >= 16 && Y <= 74 && currentImageIndex == 0) currentImageIndex = 1;
                 else if (X >= 1287 && X <= 1346 && Y >= 16 && Y <= 74 && currentImageIndex == 1) currentImageIndex = 0;
                 else if (X >= 1290 && X <= 1343 && Y >= 21 && Y <= 76 && currentImageIndex == 2) currentImageIndex = 0;
                 else if (X >= 324 && X <= 611 && Y >= 275 && Y <= 489 && (currentImageIndex == 2)) {
                    SDL_DestroyWindow(window2);
                    SDL_DestroyRenderer(renderer2);
                    create = true;
                    ChessGame game;
                    game.co1vs1();
                }
                else if (X >= 750 && X <= 1040 && Y >= 215 && Y <= 486 && currentImageIndex == 2) {
                    SDL_DestroyWindow(window2);
                    SDL_DestroyRenderer(renderer2);
                    create = true;
                    ChessGameNguoiVoiMay game1;
                    game1.run();
                }
            }
        }
    }
    if (!windowDestroyed) {
        SDL_DestroyRenderer(renderer2);
        SDL_DestroyWindow(window2);
        windowDestroyed = true;
    }
    SDL_Quit();

    return 0;
}
