#ifndef CHESSGAMENGUOIVOIMAY_HPP
#define CHESSGAMENGUOIVOIMAY_HPP

#include <SDL.h>
#include <string>

class ChessGameNguoiVoiMay {
public:
    ChessGameNguoiVoiMay();
    ~ChessGameNguoiVoiMay();
    void run(int n);

private:
    int initialMouseX;
    int initialMouseY;
    int size;
    SDL_Rect figures[32];
    std::string position;
    int board[8][8];
    std::string chess[7];
    std::string row[8];
    std::string col[8];
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* gBoardTexture;
    SDL_Texture* gChessTexture;
    SDL_Texture* gGameOverTexture;
    int selectedPieceIndex;
    bool quit;
    bool isMousePressed;
    bool isPositionInsideRect(int x, int y, const SDL_Rect& rect);
    void handlePieceMovement(int mouseX, int mouseY);
    bool isValidMove(int startRow, int startCol, int targetRow, int targetCol);
    void loadPosition();
    void stockfishMove(const std::string move);
    bool isCastling(const std::string a, int val);
    void castling(std::string a);

};

#endif // CHESSGAMENGUOIVOIMAY_HPP
