#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

// Kích thước cửa sổ
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

// Vị trí của hình ảnh
int imageX = 0;
int imageY = 0;

// Kiểm tra xem có đang giữ chuột không
bool isMousePressed = false;

void initSDL() {

    gWindow = SDL_CreateWindow("Drag Image with SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int imgFlags = IMG_INIT_PNG;
}

void loadMedia() {
    SDL_Surface* loadedSurface = IMG_Load("figures.png");
    gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
}

void closeSDL() {
    SDL_DestroyTexture(gTexture);
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
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        SDL_Rect renderQuad = { imageX, imageY, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
        SDL_RenderCopy(gRenderer, gTexture, NULL, &renderQuad);
        SDL_RenderPresent(gRenderer);
    }
    closeSDL();
    return 0;
}
