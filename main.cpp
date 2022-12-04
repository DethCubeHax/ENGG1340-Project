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
    int err=0;
    char *cont;
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
            err=sudoku.gameHandler(player1Board);
        }

        system("clear");

        switch (err)
        {
        case 1:
            cout << "You cannot erase a pre-generated square" << endl;
            break;
        case 2:
            cout << "The command you entered is invalid" << endl;
            break;
        case 3:
            cout << "The number you entered is invalid." << endl;
            break;
        default:
            break;
        }
        
    }
    cout << "\033[1;31m"<< CURSORCHAR <<"\033[0m" << endl;
}