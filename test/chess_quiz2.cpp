#include "chess_quiz2.hpp"


ChessQuiz2::ChessQuiz2() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    window = SDL_CreateWindow("The Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 499, 499, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* boardSurface = IMG_Load("images/board.png");
    gBoardTexture = SDL_CreateTextureFromSurface(renderer, boardSurface);
    SDL_FreeSurface(boardSurface);
    gChessTexture = IMG_LoadTexture(renderer, "images/figures.png");

    font = TTF_OpenFont("ARIALBI.ttf", 16);
    if (!font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        exit(1);
    }

    row = {"a","b","c","d","e","f","g","h"};
    col = {"1","2","3","4","5","6","7","8"};
    playerMove = {"h5g5"};
    botMove = {"f8e7"};

    size = 56;
    initialMouseX = 0;
    initialMouseY = 0;
    selectedPieceIndex = -1;
    isMousePressed = false;
    title = "Can you find the brilliant move ?";


    int initialBoard[8][8] = {
        {-1, 0, -3, 0, 0, -5, 0, 0},
        {-6, -6, 0, -2, -1, -6, 0, 4},
        {0, 0, 0, 0, -6, -3, 0, 6},
        {0, -4, 0, -6, 0, 0, -6, 1},
        {0, 0, 0, 6, 0, 0, 0, 0},
        {0, 0, 1, 0, 6, 0, 0, 0},
        {6, 6, 0, 0, 0, 6, 6, 0},
        {0, 3, 0, 0, 5, 0, 0, 0}
    };
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = initialBoard[i][j];
        }
    }
}
ChessQuiz2::~ChessQuiz2() {
    SDL_DestroyTexture(gBoardTexture);
    SDL_DestroyTexture(gChessTexture);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}
bool ChessQuiz2::isPositionInsideRect(int x, int y, const SDL_Rect& rect) {
    return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h);
}
void ChessQuiz2::handlePieceMovement(int mouseX, int mouseY) {
    if (selectedPieceIndex != -1) {
        figures[selectedPieceIndex].x = mouseX - 25;
        figures[selectedPieceIndex].y = mouseY - 25;
    }
}

void ChessQuiz2::x(std::string move) {
    int X1 = int(move[0]) - 97;
    int Y1 = (move[1] - '0') - 1;
    int X2 = int(move[2]) - 97;
    int Y2 = (move[3] - '0') - 1;
    board[7-Y2][X2] = board[7-Y1][X1];
    board[7-Y1][7-X1] = 0;
}
bool ChessQuiz2::isValidMove(int startRow, int startCol, int targetRow, int targetCol) {
    return (targetRow >= 0 && targetRow < 8 && targetCol >= 0 && targetCol < 8 && ((targetRow != startRow) || (targetCol != startCol)));
}
void ChessQuiz2::loadPosition() {
    int k = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int n = board[i][j];
            if (!n) continue;
            int chessWidth = 56;
            int chessHeight = 56;
            int chessX = (abs(n) - 1) * chessWidth;
            int chessY = (n > 0 ? 1 : 0) * chessHeight;
            figures[k].x = size * j + 25;
            figures[k].y = size * i + 25;
            figures[k].w = size;
            figures[k].h = size;
            SDL_Rect sourceRect = {chessX, chessY, chessWidth, chessHeight};
            SDL_RenderCopy(renderer, gChessTexture, &sourceRect, &figures[k]);
            k++;
        }
    }
}

void ChessQuiz2::run2(int valImage) {
    bool quit = false;
    int i = 0;
    int valCorlor = 0;
    int dem = 0;
    while (!quit) {
        SDL_Color textColor = {255, valCorlor, valCorlor};
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, title.c_str(), textColor);
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);
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
                        int startCol = (initialMouseX - 25) / size;
                        int startRow = (initialMouseY - 25) / size;
                        int targetCol = (event.button.x - 25) / size;
                        int targetRow = (event.button.y - 25) / size;
                        if (isValidMove(startRow, startCol, targetRow, targetCol)) {
                            Move += row[startCol];
                            Move += col[7-startRow];
                            Move += row[targetCol];
                            Move += col[7-targetRow];
                            std::cout << Move << std::endl;
                            if(Move != playerMove[0])
                            {
                               if(valImage %2 != 0) playErrorMusic();
                                Move = "";
                                title = "Incorrect, Please try again!";
                                continue;
                            }
                            board[targetRow][targetCol] = board[startRow][startCol];
                            board[startRow][startCol] = 0;
                            if(Move == playerMove[0]){
                               if(valImage %2 != 0) playVictoryMusic();
                                title = "Correct, This is the brilliant move !!!";
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
        int screenWidth, screenHeight;
        SDL_GetWindowSize(window, &screenWidth, &screenHeight);
        int textWidth, textHeight;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
        int textX = (screenWidth - textWidth) / 2;
        int textY = 7 ;
        SDL_Rect textRect = {textX, textY, textWidth, textHeight};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);
        if(dem % 2 == 0) valCorlor = 255;
        if(dem % 2 != 0) valCorlor = 0;
        dem++;
        SDL_Delay(500);
    }
    for(int i = 0; i < 10; i++) Mix_CloseAudio();
}

