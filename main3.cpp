#include "chess_game_1vs1.cpp"
#include "chess_game_nguoi_voi_may.cpp"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

SDL_Window* windowMenu;
SDL_Texture* gMenuTexture;
SDL_Renderer* rendererMenu;
SDL_Surface* menuSurface;
int X, Y;


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    windowMenu = SDL_CreateWindow("The Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,800, 600, SDL_WINDOW_SHOWN);
    rendererMenu = SDL_CreateRenderer(windowMenu, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* menuSurface = IMG_Load("chesscc.png");
    gMenuTexture = SDL_CreateTextureFromSurface(rendererMenu, menuSurface);
    bool quit = false;
    while(!quit)
    {
        SDL_Event event2;
        while(SDL_PollEvent(&event2) != 0)
        {
            if(event2.type == SDL_QUIT)
            {
                quit = true;
                return 0;
            }
            else if(event2.type == SDL_MOUSEBUTTONDOWN)
            {
               // quit = true;
                 X = event2.button.x;
                 Y = event2.button.y;
                  //cout << X << " " << Y << endl;
                  if((X >= 530 && X <= 740 && Y >= 370 && Y <= 430) || (X >= 530 && X <= 740 && Y >= 367 && Y <= 430))
                    quit = true;

            }
        }
        SDL_RenderClear(rendererMenu);
        SDL_RenderCopy(rendererMenu, gMenuTexture, NULL, NULL);
        SDL_RenderPresent(rendererMenu);
    }
    SDL_DestroyTexture(gMenuTexture);
    SDL_DestroyRenderer(rendererMenu);
    SDL_DestroyWindow(windowMenu);
    SDL_Quit();
    if (X >= 530 && X <= 740 && Y >= 370 && Y <= 430)
    {
        ChessGame game;
        game.co1vs1();
    }
    if (X >= 530 && X <= 740 && Y >= 367 && Y <= 430)
    {
        ChessGameNguoiVoiMay game1;
        game1.run();
    }

    return 0;
}
