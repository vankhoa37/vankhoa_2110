#ifndef CHESS_QUIZ3_HPP
#define CHESS_QUIZ3_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "music.hpp"

class ChessQuiz3 {
public:
    ChessQuiz3();
    ~ChessQuiz3();
    void run3();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* gBoardTexture;
    SDL_Texture* gChessTexture;
    SDL_Texture* textTexture;
    TTF_Font* font;
    std::vector<std::string> row;
    std::vector<std::string> col;
    int board[8][8];
    SDL_Rect figures[32];
    int initialMouseX;
    int initialMouseY;
    int size;
    int selectedPieceIndex;
    bool isMousePressed;
    std::string title;
    std::vector<std::string> playerMove;
    std::vector<std::string> botMove;

    bool isPositionInsideRect(int x, int y, const SDL_Rect& rect);
    void handlePieceMovement(int mouseX, int mouseY);
    void x(std::string move);
    bool isValidMove(int startRow, int startCol, int targetRow, int targetCol);
    void loadPosition();
    bool checkWin();
};

#endif /* CHESS_QUIZ2_HPP */
