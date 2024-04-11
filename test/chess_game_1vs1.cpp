#include "chess_game_1vs1.hpp"
#include "choosechesspromote.hpp"

ChessGame::ChessGame() {
    initialMouseX = 0;
    initialMouseY = 0;
    size = 56;
    quit = false;
    isMousePressed = false;
    selectedPieceIndex = -1;

    board = {
        {-1, -2, -3, -4, -5, -3, -2, -1},
        {-6, -6, -6, -6, -6, -6, -6, -6},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {6, 6, 6, 6, 6, 6, 6, 6},
        {1, 2, 3, 4, 5, 3, 2, 1}
    };

    chess = {"0","rock","knight","bishop","queen","king","pawn"};
    row = {"a","b","c","d","e","f","h"};
    col = {"1","2","3","4","5","6","7","8"};

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("The Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 453 + 46, 453 + 46, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* boardSurface = IMG_Load("images/board.png");
    gBoardTexture = SDL_CreateTextureFromSurface(renderer, boardSurface);
    SDL_Surface* boardSurface2 = IMG_Load("images/board2.png");
    gBoardTexture2 = SDL_CreateTextureFromSurface(renderer, boardSurface2);
    SDL_FreeSurface(boardSurface);
    SDL_FreeSurface(boardSurface2);
    gChessTexture = IMG_LoadTexture(renderer, "images/figures.png");
}

void ChessGame::co1vs1() {
    int val = 0;
    while (!quit) {
        SDL_Event event;
        std::string Move = "";
        std::string check = " ";
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
                        int startCol = (initialMouseX - 23) / size;
                        int startRow = (initialMouseY - 23) / size;
                        int targetCol = (event.button.x - 23) / size;
                        int targetRow = (event.button.y - 23) / size;
                        if (isValidMove(startRow, startCol, targetRow, targetCol)) {
                            if(val % 2 == 0)
                            {
                                if (targetRow == 0 && abs(board[startRow][startCol]) == 6 )
                                {
                                    int k = choose();
                                    board[startRow][startCol] = k;
                                }
                                board[targetRow][targetCol] = board[startRow][startCol];
                                board[startRow][startCol] = 0;
                            }
                            if(val % 2 != 0)
                            {
                                if (targetRow == 0 && abs(board[7-startRow][startCol]) == 6 )
                                    {
                                        int k = choose();
                                        board[7-startRow][startCol] = k * (-1);
                                    }
                                board[7-targetRow][targetCol] = board[7-startRow][startCol];
                                board[7-startRow][startCol] = 0;
                            }

                            Move += chess[abs(board[targetRow][targetCol])];
                            Move += check;
                            Move += row[targetCol];
                            Move += col[targetRow];
                            std::cout << Move << std::endl;
                            val ++;
                        }
                        selectedPieceIndex = -1;
                    }
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                handlePieceMovement(event.motion.x, event.motion.y);
            }
        }

        SDL_RenderClear(renderer);
        if(val % 2 == 0)
        SDL_RenderCopy(renderer, gBoardTexture, NULL, NULL);
        if(val % 2 != 0)
        SDL_RenderCopy(renderer, gBoardTexture2, NULL, NULL);
        loadPosition(val);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(gBoardTexture);
    SDL_DestroyTexture(gBoardTexture2);
    SDL_DestroyTexture(gChessTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool ChessGame::isPositionInsideRect(int x, int y, const SDL_Rect& rect) {
    return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h);
}

void ChessGame::handlePieceMovement(int mouseX, int mouseY) {
    if (selectedPieceIndex != -1) {
        figures[selectedPieceIndex].x = mouseX - size / 2;
        figures[selectedPieceIndex].y = mouseY - size / 2;
    }
}

bool ChessGame::isValidMove(int startRow, int startCol, int targetRow, int targetCol) {
    return (targetRow >= 0 && targetRow < 8 && targetCol >= 0 && targetCol < 8&&((startCol != targetCol )|| (startRow != targetRow)));
}

void ChessGame::loadPosition(int val) {
    int k = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            int n = board[i][j];
            if (!n) continue;
            int chessWidth = 56;
            int chessHeight = 56;
            int chessX = (abs(n) - 1) * chessWidth;
            int chessY = (n > 0 ? 1 : 0) * chessHeight;
            figures[k].x = size * j + 23;
            if(val %2 == 0)
            figures[k].y = size * i  + 23;
            if(val %2 !=0)
            figures[k].y = size * (7 - i)  + 23;
            figures[k].w = size;
            figures[k].h = size;

            SDL_Rect sourceRect = {chessX, chessY, chessWidth, chessHeight};
            SDL_RenderCopy(renderer, gChessTexture, &sourceRect, &figures[k]);
            k++;
        }
}

ChessGame::~ChessGame() {
    SDL_DestroyTexture(gBoardTexture);
    SDL_DestroyTexture(gBoardTexture2);
    SDL_DestroyTexture(gChessTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
