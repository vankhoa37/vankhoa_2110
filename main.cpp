#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gBoardTexture = NULL; 
SDL_Texture* gFiguresTexture = NULL;  
int imageX = 38;
int imageY = 38;
bool isMousePressed = false;

const int size = 56;

void initSDL() {
    gWindow = SDL_CreateWindow("Drag Image with SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int imgFlags = IMG_INIT_PNG;
}

void loadMedia() {
    SDL_Surface* boardSurface = IMG_Load("board.png");
    gBoardTexture = SDL_CreateTextureFromSurface(gRenderer, boardSurface);
   SDL_FreeSurface(boardSurface);
    SDL_Surface* figuresSurface = IMG_Load("figures.png");
    gFiguresTexture = SDL_CreateTextureFromSurface(gRenderer, figuresSurface);
    SDL_FreeSurface(figuresSurface);
}

void closeSDL() {
    SDL_DestroyTexture(gBoardTexture);
    SDL_DestroyTexture(gFiguresTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    initSDL();
    loadMedia();
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    isMousePressed = true;
                }
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    isMousePressed = false;
                }
            } else if (e.type == SDL_MOUSEMOTION) {
                if (isMousePressed) {
                    imageX = e.motion.x;
                    imageY = e.motion.y;
                }
            }
        }

        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, gBoardTexture, NULL, NULL);
        SDL_Rect figureRect = { imageX, imageY, size, size };
        SDL_Rect sourceRect = { 0, 0, size, size };
        SDL_Rect destinationRect = { imageX, imageY, size, size };
        SDL_RenderCopy(gRenderer, gFiguresTexture, &sourceRect, &destinationRect);
        SDL_RenderPresent(gRenderer);
    }

    closeSDL();
    return 0;
}
