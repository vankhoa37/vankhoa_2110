#ifndef CHESS_GAME_1vs1_HPP
#define CHESS_GAME_1vs1_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>

class ChessGame {
private:
    int initialMouseX;
    int initialMouseY;
    int size;
    SDL_Rect figures[32];
    std::vector<std::vector<int>> board;
    std::vector<std::string> chess;
    std::vector<std::string> row;
    std::vector<std::string> col;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* gBoardTexture;
    SDL_Texture* gChessTexture;
    SDL_Texture* gBoardTexture2;
    int selectedPieceIndex;
    bool quit;
    bool isMousePressed;
    bool isPositionInsideRect(int x, int y, const SDL_Rect& rect);
    void handlePieceMovement(int mouseX, int mouseY);
    bool isValidMove(int startRow, int startCol, int targetRow, int targetCol);
    void loadPosition(int val);

public:
    ChessGame();
    void co1vs1();
    ~ChessGame();
};

#endif // CHESS_GAME_1vs1_HPP
