#include "chess_game.cpp"
#include "chess_game_nguoi_voi_may.cpp"

int main(int argc, char* argv[]) {
    ChessGame game;
    game.co1vs1();
    ChessGameNguoiVoiMay game1;
    game1.run();
    return 0;
}

