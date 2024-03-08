#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
int initialMouseX = 0;
int initialMouseY = 0;

int size = 56;
SDL_Rect figures[32];
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
    // Check if the target position is within the chessboard boundaries
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
            int chessY = (n > 0 ? 1 : 0) * chessHeight;
            figures[k].x = size * j + 23;
            figures[k].y = size * i + 23;
            figures[k].w = size;
            figures[k].h = size;

            SDL_Rect sourceRect = {chessX, chessY, chessWidth, chessHeight};
            SDL_RenderCopy(renderer, gChessTexture, &sourceRect, &figures[k]);
            k++;
        }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("The Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 453 + 46, 453 + 46, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* boardSurface = IMG_Load("board.png");
    gBoardTexture = SDL_CreateTextureFromSurface(renderer, boardSurface);
    SDL_FreeSurface(boardSurface);
    gChessTexture = IMG_LoadTexture(renderer, "images/figures.png");

    bool quit = false;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    for (int i = 0; i < 32; i++) {
                        if (isPositionInsideRect(event.button.x, event.button.y, figures[i])) {
                            selectedPieceIndex = i;

                            // Store the initial mouse position when selecting a piece
                            // (Assuming a valid piece is selected)
                            initialMouseX = event.button.x;
                            initialMouseY = event.button.y;
                            break;
                        }
                    }
                }
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (selectedPieceIndex != -1) {
                        // Calculate the board coordinates for the initial mouse position
                        int startCol = (initialMouseX - 23) / size;
                        int startRow = (initialMouseY - 23) / size;

                        // Calculate the board coordinates for the target mouse position
                        int targetCol = (event.button.x - 23) / size;
                        int targetRow = (event.button.y - 23) / size;

                        // Update the board only if the move is valid
                        if (isValidMove(startRow, startCol, targetRow, targetCol)) {
                            board[targetRow][targetCol] = board[startRow][startCol];
                            board[startRow][startCol] = 0;
                        }

                        // Clear the selection
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
