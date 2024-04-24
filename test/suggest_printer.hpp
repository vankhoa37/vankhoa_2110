#ifndef SUGGEST_PRINTER_HPP
#define SUGGEST_PRINTER_HPP
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class SuggestPrinter {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Surface* boardSurface;

public:
    SuggestPrinter() : window(nullptr), renderer(nullptr), font(nullptr), boardSurface(nullptr) {}
    ~SuggestPrinter() { close(); }

    void init() {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Suggest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 499, 499, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        TTF_Init();
        font = TTF_OpenFont("font.ttf", 50);
        boardSurface = IMG_Load("images/background_suggest.jpg");
        if (!boardSurface) {
            std::cerr << "Failed to load board image." << std::endl;
        }
    }

    void close() {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }
        if (window) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
        if (font) {
            TTF_CloseFont(font);
            font = nullptr;
        }
        if (boardSurface) {
            SDL_FreeSurface(boardSurface);
            boardSurface = nullptr;
        }

        TTF_Quit();
        //SDL_Quit();
    }

    void printSuggest(const std::string& str) {
    SDL_Color textColor = {255, 0, 0 , 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, str.c_str(), textColor);
    if (!textSurface) {
        return;
    }

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    int x = (windowWidth - textWidth) / 2;
    int y = (windowHeight - textHeight) / 2;

    SDL_Texture* boardTexture = SDL_CreateTextureFromSurface(renderer, boardSurface);
    SDL_RenderCopy(renderer, boardTexture, NULL, NULL);

    SDL_Rect textRect = {x, y, textWidth, textHeight};
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_RenderPresent(renderer);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(boardTexture);
}

};

#endif
