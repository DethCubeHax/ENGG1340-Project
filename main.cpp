#include <iostream>
#include "Sudoku.h"
#include "GlobalVars.h"
using namespace std;
Sudoku sudoku;

int player1Board[SIZE][SIZE] = {0};
int tmpBoard[SIZE][SIZE] = {0};

BoardState *playerBoardHead = NULL;
BoardState *computerBoardHead = NULL;

int main()
{
    bool generated = false;
    while (choice != "exit"){
        if (choice == "")
        {
            sudoku.welcome();
        }
        if (choice == "2"){
            if (generated == false){
                sudoku.generateBoard(player1Board);
                generated = true;
            }
            sudoku.gameHandler(player1Board);
        }
    }
    cout << "\033[1;31m"<< CURSORCHAR <<"\033[0m" << endl;
}