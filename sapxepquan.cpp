#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int size = 56;
SDL_Texture* chessTexture;
SDL_Rect figures[32];
int board[8][8] = {
    {-1, -2, -3, -4, -5, -3, -2, -1},
    {-6, -6, -6, -6, -6, -6, -6, -6},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {6, 6, 6, 6, 6, 6, 6, 6},
    {1, 2, 3, 4, 5, 3, 2, 1}
};

SDL_Window* window;
SDL_Renderer* renderer;

void loadPosition()
{
    int k = 0;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            int n = board[i][j];
            if (!n) continue;
            int chessWidth = 56;
            int chessHeight = 56;
            int chessX = (abs(n) - 1) * chessWidth;
            int chessY = (n > 0 ? 1 : 0) * chessHeight;
            figures[k].x = size * j;
            figures[k].y = size * i;
            figures[k].w = size;
            figures[k].h = size;

            SDL_Rect sourceRect = { chessX, chessY, chessWidth, chessHeight };
            SDL_RenderCopy(renderer, chessTexture, &sourceRect, &figures[k]);
            k++;
        }
}
int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("The Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 453, 453, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    chessTexture = IMG_LoadTexture(renderer, "images/figures.png");
    bool quit = false;

    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_RenderClear(renderer);
        loadPosition();
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyTexture(chessTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
