#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include "music.hpp"
#include "SDL2ImageRenderer.hpp"
#include "chess_game_1vs1.cpp"
#include "chess_game_nguoi_voi_may.cpp"
#include "suggest_printer.hpp"
#include "chess_quiz.cpp"
#include "chess_quiz2.cpp"
#include "chess_quiz3.cpp"
using namespace std;

const int WINDOW_WIDTH = 1368;
const int WINDOW_HEIGHT = 707;
bool create = false;
bool windowDestroyed = false;
vector<string> imagePaths = {"images/menugame1_1.jpg", "images/menugame1_2.jpg", "images/menugamechess2_1.jpg", "images/menugamechess2_2.jpg", "images/quizmenu1.jpg", "images/quizmenu2.jpg"};
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
    playMusic();
    Mix_PauseMusic();
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
                 else if (X >= 254 && X <= 546 && Y >= 390 && Y <= 465 && currentImageIndex == 1) currentImageIndex = 3;

                 else if (X >= 1287 && X <= 1346 && Y >= 16 && Y <= 74 && currentImageIndex == 0) currentImageIndex = 1;
                 else if (X >= 1287 && X <= 1346 && Y >= 16 && Y <= 74 && currentImageIndex == 1) currentImageIndex = 0;
                 else if (X >= 1209 && X <= 1267 && Y >= 21 && Y <= 76 && currentImageIndex == 2) currentImageIndex = 3;
                 else if (X >= 1209 && X <= 1267 && Y >= 21 && Y <= 76 && currentImageIndex == 3) currentImageIndex = 2;
                 else if (X >= 1209 && X <= 1267 && Y >= 21 && Y <= 76 && currentImageIndex == 4) currentImageIndex = 5;
                 else if (X >= 1209 && X <= 1267 && Y >= 21 && Y <= 76 && currentImageIndex == 5) currentImageIndex = 4;
                 else if (X >= 1290 && X <= 1343 && Y >= 21 && Y <= 76 && currentImageIndex == 2) currentImageIndex = 0;
                 else if (X >= 1290 && X <= 1343 && Y >= 21 && Y <= 76 && currentImageIndex == 3) currentImageIndex = 1;
                 else if (X >= 1290 && X <= 1343 && Y >= 21 && Y <= 76 && currentImageIndex == 5) currentImageIndex = 1;
                 else if (X >= 1290 && X <= 1343 && Y >= 21 && Y <= 76 && currentImageIndex == 4) currentImageIndex = 0;
                 else if (X >= 732 && X <= 1022 && Y >= 485 && Y <= 557 && currentImageIndex == 0) currentImageIndex = 4;
                 else if (X >= 732 && X <= 1022 && Y >= 485 && Y <= 557 && currentImageIndex == 1) currentImageIndex = 5;
                 if(currentImageIndex % 2 != 0) Mix_ResumeMusic();
                 if(currentImageIndex % 2 == 0) Mix_PauseMusic();
                 else if (X >= 324 && X <= 611 && Y >= 275 && Y <= 489 && (currentImageIndex == 2 || currentImageIndex == 3)) {
                    SDL_DestroyWindow(window2);
                    SDL_DestroyRenderer(renderer2);
                    create = true;
                    ChessGame game;
                    game.co1vs1();
                    Mix_CloseAudio();
                    playMusic();
                }
                else if (X >= 750 && X <= 1040 && Y >=215 && Y <= 486 && (currentImageIndex == 2 || currentImageIndex == 3)) {
                    SDL_DestroyWindow(window2);
                    SDL_DestroyRenderer(renderer2);
                    create = true;
                    ChessGameNguoiVoiMay game1;
                    game1.run(0);
                }
                else if (X >= 182 && X <= 604 && Y >= 287 && Y <= 403 && (currentImageIndex == 4 || currentImageIndex == 5 )) {
                    SDL_DestroyWindow(window2);
                    SDL_DestroyRenderer(renderer2);
                    create = true;
                    ChessQuiz quiz;
                    quiz.run();
                }
                else if (X >= 755 && X <= 1174 && Y >= 287 && Y <= 403 && (currentImageIndex == 4 || currentImageIndex == 5 )) {
                    SDL_DestroyWindow(window2);
                    SDL_DestroyRenderer(renderer2);
                    create = true;
                    ChessQuiz2 quiz;
                    quiz.run2();
                }
                else if (X >= 182 && X <= 604 && Y >= 467 && Y <= 581 && (currentImageIndex == 4 || currentImageIndex == 5 )) {
                    SDL_DestroyWindow(window2);
                    SDL_DestroyRenderer(renderer2);
                    create = true;
                    ChessQuiz3 quiz;
                    quiz.run3();
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
