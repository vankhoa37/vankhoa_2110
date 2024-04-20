#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
using namespace std;
int initialMouseX = 0;
int initialMouseY = 0;
int size = 56;
SDL_Rect figures[32];
int board[8][8] = {
    {0, -5, -3, 0, 0, 0, 0, 0},
    {0, 0, -6, 0, 0, 0, -6, 0},
    {0, -6, 0, 0, -4, 0, 0, -6},
    {0, 4, 0, 0, 2, -6, 0, 6},
    {0, 0, 6, 0, 0, 6, 0, 0},
    {0, 0, 0, 6, 0, 0, 6, 0},
    {0, 0, 5, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};
 string playerMove[3] = {"e4c3", "b4a5", "c3d1"};
 string botMove[2] = {"b1a1", "a1b2"};
 string title = "Checkmate in 4 !!";
//string chess[7] = {"0","rock","knight","bishop","queen","king","pawn"};
string row[8] = {"a","b","c","d","e","f","g","h"};
string col[8] = {"1","2","3","4","5","6","7","8"};
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* gBoardTexture = NULL;
SDL_Texture* gChessTexture = NULL;
int selectedPieceIndex = -1;
bool isMousePressed = false;
bool isPositionInsideRect(int x, int y, const SDL_Rect& rect) {
    return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h);
}
void handlePieceMovement(int mouseX, int mouseY) {
    if (selectedPieceIndex != -1) {
        figures[selectedPieceIndex].x = mouseX - 25;
        figures[selectedPieceIndex].y = mouseY - 25;
    }
}
void x(string move)
{
    int X1 = int(move[0]) - 97;
    int Y1 = (move[1] - '0') - 1;
    int X2 = int(move[2]) - 97;
    int Y2 = (move[3] - '0') - 1;
    board[Y2][X2] = board[Y1][X1];
    board[Y1][X1] = 0;
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
            figures[k].x = size * j + 25;
            figures[k].y = size * i + 25;
            figures[k].w = size;
            figures[k].h = size;
            // figures[]: vi tri dat quan tren ban co
            // sourceRect : vi tri cat anh figures.png
            SDL_Rect sourceRect = {chessX, chessY, chessWidth, chessHeight};
            SDL_RenderCopy(renderer, gChessTexture, &sourceRect, &figures[k]);
            k++;
        }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("The Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 499, 499, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* boardSurface = IMG_Load("images/board.png");
    gBoardTexture = SDL_CreateTextureFromSurface(renderer, boardSurface);
    SDL_FreeSurface(boardSurface);
    gChessTexture = IMG_LoadTexture(renderer, "images/figures.png");
    bool quit = false;
    int i = 0;
    while (!quit) {
            //cout << title << endl;
        SDL_Event event;
        string Move = "";
        string check = " ";
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
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (selectedPieceIndex != -1) {
                        for(int i = 0; i < 32 ; i++)
                           if(isPositionInsideRect(event.button.x, event.button.y, figures[i]))
                              if(i != selectedPieceIndex) check = " x";
                        int startCol = (initialMouseX - 25) / size;
                        int startRow = (initialMouseY - 25) / size;
                        int targetCol = (event.button.x - 25) / size;
                        int targetRow = (event.button.y - 25) / size;
                        if (isValidMove(startRow, startCol, targetRow, targetCol)) {
                            Move += row[startCol];
                            Move += col[startRow];
                            Move += row[targetCol];
                            Move += col[targetRow];
                            cout << Move << endl;
                            if(Move != playerMove[i])
                            {
                                Move = "";
                                continue;
                            }
                            board[targetRow][targetCol] = board[startRow][startCol];
                            board[startRow][startCol] = 0;

                            if(i<2)
                            {
                               x(botMove[i]);
                               i++;
                            }

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
