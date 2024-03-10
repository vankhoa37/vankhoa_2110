#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <time.h>
#include "Connector.hpp"
using namespace std;
int initialMouseX = 0;
int initialMouseY = 0;
int size = 56;
SDL_Rect figures[32];
string position = "";
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
string chess[7] = {"0","rock","knight","bishop","queen","king","pawn"};
string row[8] = {"a", "b", "c", "d", "e", "f", "g", "h"};
string col[8] = {"1","2","3","4","5","6","7","8"};
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* gBoardTexture = NULL;
SDL_Texture* gChessTexture = NULL;
int selectedPieceIndex = -1;
bool quit;
bool isMousePressed = false;
bool isPositionInsideRect(int x, int y, const SDL_Rect& rect) {
    return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h);
}
void handlePieceMovement(int mouseX, int mouseY) {
    if (selectedPieceIndex != -1) {
        figures[selectedPieceIndex].x = mouseX - size / 2;
        figures[selectedPieceIndex].y = mouseY - size / 2;
    }
}
bool isValidMove(int startRow, int startCol, int targetRow, int targetCol) {
    return (targetRow >= 0 && targetRow < 8 && targetCol >= 0 && targetCol < 8);
}
void loadPosition() {
    int k = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            int n = board[i][j];
            if (!n) continue;
            int chessWidth = 56;
            int chessHeight = 56;
            int chessX = (abs(n) - 1) * chessWidth;
            int chessY = (n < 0 ? 1 : 0) * chessHeight;
            figures[k].x = size * j + 23;
            figures[k].y = size * i + 23;
            figures[k].w = size;
            figures[k].h = size;
            // figures[]: vi tri dat quan tren ban co
            // sourceRect : vi tri cat anh figures.png
            SDL_Rect sourceRect = {chessX, chessY, chessWidth, chessHeight};
            SDL_RenderCopy(renderer, gChessTexture, &sourceRect, &figures[k]);
            k++;
        }
}
void stockfishMove(const std::string move) {
    int X1 = int(move[0]) - 97;
    int Y1 = (move[1] - '0') - 1;
    int X2 = int(move[2]) - 97;
    int Y2 = (move[3] - '0') - 1;
   // cout << X1 << Y1 << X2 << Y2 << endl;
    //cout << board[Y1][X1];

    //cout << "quan co duoc stockfish chon la " << i;
    board[Y2][X2] = board[Y1][X1];
    board[Y1][X1] = 0;
    //cout << board[Y1][X1];
    std::cout << " doi nuoc thanh cong  " << endl;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("The Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 453 + 46, 453 + 46, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* boardSurface = IMG_Load("board.png");
    gBoardTexture = SDL_CreateTextureFromSurface(renderer, boardSurface);
    SDL_FreeSurface(boardSurface);
    gChessTexture = IMG_LoadTexture(renderer, "images/figures.png");
    ConnectToEngine("stockfish.exe");
    bool quit = false;
    int val = 1;

    while (!quit) {
        SDL_Event event;
        string Move = "";
        string check = " ";
        if( val > 0 )
            {
                string str = getNextMove(position);
                position += str + " ";
                cout << str;
                stockfishMove(str);
                val --;

            }
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    for (int i = 0; i < 32; i++) {
                        if (isPositionInsideRect(event.button.x, event.button.y, figures[i])) {
                            selectedPieceIndex = i;
                            initialMouseX = event.button.x;
                            initialMouseY = event.button.y;
                            break;
                        }
                    }
                }
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                val++;
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (selectedPieceIndex != -1) {
                        for(int i = 0; i < 32 ; i++)
                           if(isPositionInsideRect(event.button.x, event.button.y, figures[i]))
                              if(i != selectedPieceIndex) check = " x";
                        int startCol = (initialMouseX - 23) / size;
                        int startRow = (initialMouseY - 23) / size;
                        int targetCol = (event.button.x - 23) / size;
                        int targetRow = (event.button.y - 23) / size;
                        if (isValidMove(startRow, startCol, targetRow, targetCol)) {
                            board[targetRow][targetCol] = board[startRow][startCol];
                            board[startRow][startCol] = 0;
                           // Move += chess[abs(board[targetRow][targetCol])];
                            //Move += check;
                            Move += row[startCol];
                            Move += col[startRow];
                            Move += row[targetCol];
                            Move += col[targetRow];
                            //cout << Move << endl;
                            cout << Move << endl;
                            position += Move + " ";
                        }
                        selectedPieceIndex = -1;
                    }
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                handlePieceMovement(event.motion.x, event.motion.y);
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, gBoardTexture, NULL, NULL);
        loadPosition();
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(gBoardTexture);
    SDL_DestroyTexture(gChessTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
