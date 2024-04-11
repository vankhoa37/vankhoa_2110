#include "chess_game_nguoi_voi_may.hpp"
#include <SDL_image.h>
#include <SDL.h>
#include <iostream>
#include <time.h>
#include <SDL_mixer.h>
#include "connector1.hpp"
#include "promotechess.hpp"

using namespace std;

ChessGameNguoiVoiMay::ChessGameNguoiVoiMay() : initialMouseX(0), initialMouseY(0), size(56), position(""), selectedPieceIndex(-1), quit(false), isMousePressed(false) {
    int initialBoard[8][8] = {
        {-1, -2, -3, -4, -5, -3, -2, -1},
        {-6, -6, -6, -6, -6, -6, -6, -6},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {6, 6, 6, 6, 6, 6, 6, 6},
        {1, 2, 3, 4, 5, 3, 2, 1}
    };
    std::copy(&initialBoard[0][0], &initialBoard[0][0] + 8 * 8, &board[0][0]);

    // Initialize strings
    chess[0] = "0";
    chess[1] = "rock";
    chess[2] = "knight";
    chess[3] = "bishop";
    chess[4] = "queen";
    chess[5] = "king";
    chess[6] = "pawn";
    row[0] = "a";
    row[1] = "b";
    row[2] = "c";
    row[3] = "d";
    row[4] = "e";
    row[5] = "f";
    row[6] = "g";
    row[7] = "h";
    col[0] = "1";
    col[1] = "2";
    col[2] = "3";
    col[3] = "4";
    col[4] = "5";
    col[5] = "6";
    col[6] = "7";
    col[7] = "8";

    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("The Chess With Bot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 453 + 46, 453 + 46, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* boardSurface = IMG_Load("images/board.png");
    gBoardTexture = SDL_CreateTextureFromSurface(renderer, boardSurface);
    SDL_FreeSurface(boardSurface);
    gChessTexture = IMG_LoadTexture(renderer, "images/figures.png");
    ConnectToEngine("stockfish.exe");
}

ChessGameNguoiVoiMay::~ChessGameNguoiVoiMay() {
    SDL_DestroyTexture(gBoardTexture);
    SDL_DestroyTexture(gChessTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void ChessGameNguoiVoiMay::run() {
    playMusic();
    int val = 1;
    while (!quit) {
        SDL_Event event;
        std::string Move = "";
        std::string check = " ";
        if (val > 0) {
                string str = getNextMove(position);
                cout << str << endl;
                cout << str[0] << str[1];
                cout << "vi tri : "  <<  int(str[0] ) - 97 << " "  << str[1] - '0' - 1 << endl;
                if(isPromote(str, board[str[1]-'0' - 1][int(str[0]) - 97]))
                            {
                                cout << "phat hien promote    " << endl;
                                str = getNextMovePromote(position);
                                stockfishMovePromote(str, board[str[1]-'0' - 1][int(str[0]) - 97]);

                            }
                    stockfishMove(str);
                    position += str + " ";
                if (isCastling(str))
                {
                    castling(str);
                }
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
                        for (int i = 0; i < 32; i++)
                            if (isPositionInsideRect(event.button.x, event.button.y, figures[i]))
                                if (i != selectedPieceIndex) check = " x";
                        int startCol = (initialMouseX - 23) / size;
                        int startRow = (initialMouseY - 23) / size;
                        int targetCol = (event.button.x - 23) / size;
                        int targetRow = (event.button.y - 23) / size;
                        if (isValidMove(startRow, startCol, targetRow, targetCol)) {
                            Move += row[startCol];
                            Move += col[startRow];
                            Move += row[targetCol];
                            Move += col[targetRow];
                            std::cout << Move << std::endl;
                            if (isCastling(Move)) {
                                castling(Move);
                            }
                            board[targetRow][targetCol] = board[startRow][startCol];
                            board[startRow][startCol] = 0;
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
}

bool ChessGameNguoiVoiMay::isPositionInsideRect(int x, int y, const SDL_Rect& rect) {
    return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h);
}

void ChessGameNguoiVoiMay::handlePieceMovement(int mouseX, int mouseY) {
    if (selectedPieceIndex != -1) {
        figures[selectedPieceIndex].x = mouseX - size / 2;
        figures[selectedPieceIndex].y = mouseY - size / 2;
    }
}

bool ChessGameNguoiVoiMay::isValidMove(int startRow, int startCol, int targetRow, int targetCol) {
    return (targetRow >= 0 && targetRow < 8 && targetCol >= 0 && targetCol < 8 && (targetRow != startRow || targetCol != startCol));
}

void ChessGameNguoiVoiMay::loadPosition() {
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
            SDL_Rect sourceRect = {chessX, chessY, chessWidth, chessHeight};
            SDL_RenderCopy(renderer, gChessTexture, &sourceRect, &figures[k]);
            k++;
        }
}

void ChessGameNguoiVoiMay::stockfishMove(const std::string move) {
    int X1 = int(move[0]) - 97;
    int Y1 = (move[1] - '0') - 1;
    int X2 = int(move[2]) - 97;
    int Y2 = (move[3] - '0') - 1;

    board[Y2][X2] = board[Y1][X1];
    board[Y1][X1] = 0;
    std::cout << " doi nuoc thanh cong  " << std::endl;
}

bool ChessGameNguoiVoiMay::isCastling(const std::string a) {
    int X1 = int(a[0]) - 97;
    int Y1 = (a[1] - '0') - 1;
    int X2 = int(a[2]) - 97;
    int Y2 = (a[3] - '0') - 1;
    int king = abs(board[Y1][X1]);
    if ((a == "e1g1" || a == "e8c8" || a == "e1c1" || a == "e8g8") ) {
        std::cout << "la nhap thanh ";
        return true;
    }
    return false;
}

void ChessGameNguoiVoiMay::castling(std::string a) {
    if (a == "e1g1") stockfishMove("h1f1");
    if (a == "e8c8") stockfishMove("a8d8");
    if (a == "e1c1") stockfishMove("a1d1");
    if (a == "e8g8") stockfishMove("h8f8");
}
void ChessGameNguoiVoiMay::playMusic() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *music = Mix_LoadMUS("music.mp3");
    Mix_PlayMusic(music, 10); // Phát nhạc một lần
}
