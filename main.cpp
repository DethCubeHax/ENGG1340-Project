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
            system("clear");
            if (err != 0) err = 0;
            sudoku.welcome();
            if (choice == "exit")
            {
                system("clear");
                break;
            }
        }

        switch (err)
        {
            case 1:
                cout << "You cannot erase a pre-generated square." << endl;
                break;
            case 2:
                cout << "The command you entered is invalid." << endl;
                break;
            case 3:
                cout << "The number you entered is invalid." << endl;
                break;
            case 4:
                cout << "You cannot overwrite a pre-generated square." << endl;
                break;
            case 5:
                cout << "Game has been saved." << endl;
                choice = "";
            default:
                break;
        }
        if (choice == "1")
        {
            sudoku.loadList(computerBoardHead, tmpBoard);
            //sudoku.printBoard(tmpBoard);
            choice = "exit";
        }
        sudoku.toLowerCase(choice);
        if (choice == "2"){
            system("clear");
            if (generated == false){
                system("clear");
                sudoku.generateBoard(player1Board);
                generated = true;
            }
            err=sudoku.gameHandler(player1Board);
        }
        if (choice == "3"){
            system("clear");
            sudoku.showInstruction();
        }
        if (choice == "4"){
            system("clear");
            sudoku.finalScreen(player1Board);
        }
        if (choice == "exit"){
            
            break;
        }
    }
    cout << "\n\n\n\x1B[38;5;30m--\x1B[38;5;66m-。\x1B[38;5;102m--。\x1B[38;5;138m---";
    cout << "\x1B[38;5;174mBye \x1B[38;5;210mbye \x1B[38;5;210m(^･ω\x1B[38;5;174m･^)";
    cout << "\x1B[38;5;138m---\x1B[38;5;102m。--\x1B[38;5;66m。-\x1B[38;5;30m--\n\n\n" << endl;
}