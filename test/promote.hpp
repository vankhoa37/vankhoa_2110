#ifndef PROMOTE_H
#define PROMOTE_H
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
string Chess[4] = {"rock", "knight", "bishop", "queen"};
bool isPawn(string a)
{
    int X1 = int(a[0]) - 97;
    int Y1 = (a[1] - '0') - 1;
    int X2 = int(a[2]) - 97;
    int Y2 = (a[3] - '0') - 1;
    int k = abs(board[Y1][X1]);
    if (k == 6) return true;
    return false;
}
bool isWhite (int val)
{
	if (val > 0) return true;
	return false;
}

void promote(int &val, int col, string &position)
{
  if (isWhite(val) && col == 8) 
  cout << "Chon quan co ban muon thang cap ";
  string chess;
  cin >> chess;
  for (int i = 0; i < 4; i++)
  {
  	if(chess == Chess[i]) val = i + 1;
  	break;
  }
   position += "=" + " " + Chess[val - 1];
}
void stockfishPromote(string &position, string move)// d7d8 = queen
{
	string res = getNextMovePromote(position);
	string selectedChess;
	for(int i = 0; i < 4; i++)
	{
		int f = res.find(Chess[i]);
		if(f != -1)  selectedChess = Chess[i];
	}
	string stockfishMovePromote = move +  " = " + selectedChess;
	position += stockfishMovePromote;
	
}



#endif PROMOTE_H
