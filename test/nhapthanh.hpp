#ifndef NHAPTHANH_H
#define NHAPTHANH_H
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "test_6_2.cpp"
using namespace std;
bool isCastling (string a)
{
    int X1 = int(a[0]) - 97;
    int Y1 = (a[1] - '0') - 1;
    int X2 = int(a[2]) - 97;
    int Y2 = (a[3] - '0') - 1;
    int king = abs(board[Y1][X1]);
    if ((a == "e1g1" || a == "e8c8" || a == "e1c1" || a == "e8g8") && king == 6 )
        return true;
    return false;
}
void castling (string a)
{
    if (a == "e1g1") stockfishMove("h1f1");
    if (a == "e8c8") stockfishMove("h8f8");
    if (a == "e1c1") stockfishMove("a1d1");
    if (a == "e8g8") stockfishMove("a8d8");

}

#endif NHAPTHANH_H

