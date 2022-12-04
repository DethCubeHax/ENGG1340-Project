
#ifndef GLOBALVARS_H
#define GLOBALVARS_H
#include <string>

using namespace std;

#define SIZE 9
#define CURSORCHAR "X" // 0_0 -_- *_* +_+ !_! /_\ \_/ Q_Q A_A

extern string choice;
extern int cursorX, cursorY;

struct BoardState
{
    int board[SIZE][SIZE];
    BoardState *next;
    BoardState *previous;
    bool failed;
};

#endif
