#ifndef PROMOTECHESS_HPP
#define PROMOTECHESS_HPP
#include <SDL.h>
#include <string>
#include <iostream>
using namespace std;
char Figures[4] = {'r','k','b','q'};
bool isPawn (int val )
{
	if (abs(val) == 6) return true;
	return false;
}
bool isPromote (string move1, int val)
{
	if(isPawn(val))
	{
		int startX = move1[0] - '0' - 97;
	    int startY = move1[1] - '0';
	    int targetX = move1[2] - '0' - 97;
	    int targetY =  move1[3] - '0';
	    if (val > 0 && targetY == 1) return true;
	    if (val < 0 && targetY == 8) return true;
	}
	return false;
}
void stockfishMovePromote (string stockfishMove, int &val)
{
	    int startX = stockfishMove[0] - '0' - 97;
	    int startY = stockfishMove[1] - '0';
	    int targetX = stockfishMove[2] - '0' - 97;
	    int targetY = stockfishMove[3] - '0';
	    char figure = stockfishMove[4];
	    for(int i = 0; i < 4; i++)
	    {
	    	if(figure == Figures[i])
	    	{
	    	    if(val > 0)
	    		val = i + 1;
	    		if(val < 0)
                val = -1 * (i + 1);
	    		cout << "tim dc val la " << val;
			}
		}
}
#endif // PROMOTECHESS_HPP
