#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <random>
#include <chrono>
#include <string>
#include <cctype>
#include "Sudoku.h"
#include "GlobalVars.h"

using namespace std;
using namespace std::chrono;

random_device square; // obtain a random number from hardware
random_device number; // obtain a random number from hardware
mt19937 genSquare(square()); // seed the generator
mt19937 genNumber(number()); // seed the generator
uniform_int_distribution<> distrSquare(0, SIZE-1); // define the range
uniform_int_distribution<> distrNumber(1, SIZE); // define the range

extern BoardState *playerBoardHead;
extern BoardState *computerBoardHead;


uint64_t timeSinceBoot()
{
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

uint64_t runTime = timeSinceBoot();

bool Sudoku::numberIsPossible(int number, int x, int y, int (&board)[SIZE][SIZE])
{
    if (checkRow(number, x, board) && checkColumn(number, y, board) && checkBlock(number, x, y, board) ) return true;
    return false;
}


void Sudoku::welcome(){
    
    bool valid_input = false;
    cout << "Hello! Welcome to sudoku!" << endl;
  
    
    while (!valid_input){
        cout << "Please choose an option:" << endl;
        cout << "1. Load game" << endl;
        cout << "2. New game" << endl;
        cout << "3. Instructions" << endl;
            cin >> choice;
            cin.ignore();
            valid_input = true;
            if (choice == "1"){
                valid_input = true;
            }
            else if (choice == "2"){
                valid_input = true;
            }
            else if (choice == "3"){
                showInstruction();
                valid_input = true;
            }
            else{
                cout<<"========================================="<<endl;
                cout << "Invalid input. Please enter: [ 1 2 3 ]." <<endl;
                cout<<"========================================="<<endl;
                valid_input = false;
            }
            
        }
    }

int Sudoku::gameHandler(int (&board)[SIZE][SIZE]){
    printBoard(board);
    cout << "" << endl;
    string control;
    cin >> control;
    toLowerCase(control);
    if (control == "w" || control == "a" || control == "s" || control == "d"){
        cursorInputHandler(control);
        return 0;
    }
    if (stoi(control) == 0)
    {
        if(playerBoardHead->board[cursorY][cursorX] != 0)
        {
            cout << "INITIATING SHIELDSSS" << endl;
            return 1;
        }
        board[cursorY][cursorX] = 0;
        addToList(playerBoardHead, board);
        return 0;
    }

    else if(stoi(control) > 10 || stoi(control) < 0){
        return 2;
    }
    if(! numberIsPossible(stoi(control), cursorY, cursorX, board)){
        return 3;
    }
    else{
        board[cursorY][cursorX] = stoi(control);
        addToList(playerBoardHead, board);
        return 0;
    }
}


void Sudoku::toLowerCase(string &str){
    for (int i = 0; i < str.length(); i++){
        str[i] = tolower(str[i]);
    }
}
   
void Sudoku::cursorInputHandler(string control){
    if (control == "a" && cursorX != 0){
        cursorX--;
    }
    if (control == "d" && cursorX != 8){
        cursorX++;
    }
    if (control == "w" && cursorY != 0){
        cursorY--;
    }
    if (control == "s" && cursorY != 8){
        cursorY++;
    }
}

void Sudoku::showInstruction(){
    
    cout<<"============ Instruction ================"<<endl;
    cout<<"This game is about......"<<endl;
    cout<<"========================================="<<endl;
    cout<<"Press Enter to continue";
    cout<<"========================================="<<endl;
    // cin.ignore();
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    
}


void Sudoku::generateBoard(int (&board)[SIZE][SIZE])
{
    for (int i = 0; i<18; i++)
    {
        int x = distrSquare(genSquare);
        int y = distrSquare(genSquare);
        int num = distrNumber(genNumber);
        if (numberIsPossible(num, x, y, board) && board[x][y] == 0)
        {
            board[x][y] = num;
        }
        else
        {
            i--;
        }
    }

    int tmpBoard[SIZE][SIZE] = {0};

    copyBoard(tmpBoard, board);

    runTime = timeSinceBoot();
    if (!solveBoard(tmpBoard))
    {
        eraseBoard(board);
        generateBoard(board);
    }
    addToList(playerBoardHead, board);
}

void Sudoku::printBoard(int (&board)[SIZE][SIZE])
{
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        if ( i % 3 == 0 && i != 0 )
        {
            cout << "\u001b[36m";
            cout << "------x-------x------" << endl;
        }
        for ( int j = 0 ; j < SIZE ; j++ )
        {
            if (playerBoardHead->board[i][j] != 0)
            {
                cout << "\033[1;31m";
            }
                if (j == 3 || j == 6)
                {
                    cout << "\u001b[36m";
                    cout << "| ";
                    if (playerBoardHead->board[i][j] != 0)
                    {
                        cout << "\033[1;31m";
                    }
                    else
                    {
                        cout << "\033[0m";
                    }
                }
                if (cursorX == j && cursorY == i)
                {
                    if (playerBoardHead->board[i][j] != 0)
                    {
                        cout << "\033[1;31m";
                    }
                    else
                    {
                        cout << "\u001b[32m";
                        if (board[i][j] != 0)
                        {
                            cout << "\u001b[32m" << board[i][j] << ' ';
                            cout << "\033[0m";
                            continue;
                        }
                    }
                    cout << CURSORCHAR << ' ';
                    cout << "\033[0m";
                    continue;
                }
                if (playerBoardHead->board[i][j] == 0)
                {
                    cout << "\033[0m";
                }
                cout<<board[i][j]<<' ';
            if (playerBoardHead->board[i][j] != 0)
            {
                cout << "\033[0m";
            }
        }
        cout<<endl;
    }
}

void Sudoku::readOrSaveBoard(int (&board)[SIZE][SIZE], char args)
{   
    if (args == 'r')
    {
        ifstream fin("test.txt");                 // Open the file
        int yCount = 0;
        string line;
        while (getline(fin, line))
        {
            istringstream iss(line);
            char w;
            int xCount = 0;
            while (iss >> w)
            {
                board[yCount][xCount] = int(w) - 48;
                xCount++;
            }
            yCount++;
        }
        fin.close();
    }

    if (args == 'w')
    {
        ofstream fout("test.txt");
        for ( int i = 0 ; i < SIZE ; i++ )
        {
            for ( int j = 0 ; j < SIZE ; j++ )
            {
                fout<<board[i][j]<<' ';
            }
            fout<<endl;
        }
        fout.close();
    }
}

bool Sudoku::checkRow(int number, int y, int (&board)[SIZE][SIZE])
{
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        if ( board[y][i] == number ) return false;
    }
    return true;
}

bool Sudoku::checkColumn(int number, int x, int (&board)[SIZE][SIZE])
{
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        if ( board[i][x] == number ) return false;
    }
    return true;
}

bool Sudoku::checkBlock(int number, int x, int y, int (&board)[SIZE][SIZE])
{
    bool notIn = true;
    int xBlock = x/3;
    int yBlock = y/3;
    for ( int i = 0 ; i < 3 ; i++){
        for ( int j = 0 ; j < 3 ; j++){
            if ( board[xBlock*3+i][yBlock*3+j] == number ){
                notIn = false;
                break;
            }
        }
    }
    return notIn;
}

bool Sudoku::solveBoard(int (&board)[SIZE][SIZE])
{
    if (timeSinceBoot() - runTime > 100)
    {
        eraseList(computerBoardHead);
        return false;
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                for (int k = 1; k <= SIZE; k++)
                {
                    if (numberIsPossible(k, i, j, board))
                    {
                        board[i][j] = k;
                        addToList(computerBoardHead, board);
                        if (solveBoard(board))
                        {
                            return true;
                        }
                        else
                        {
                            board[i][j] = 0;
                            addToList(computerBoardHead, board);
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void Sudoku::addToList(BoardState *&head, int (&board)[SIZE][SIZE])
{
    BoardState *newState = new BoardState();
    copyBoard(newState->board, board);
    newState->next = NULL;
    if (head == NULL)
    {
        head = newState;
        return;
    }
    
    BoardState *traverser = head;

    while (traverser->next != NULL)
    {
        traverser = traverser->next;
    }
    traverser->next = newState;
    newState->previous = traverser;
}

void Sudoku::copyBoard(int (&board1)[SIZE][SIZE], int (&board2)[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board1[i][j] = board2[i][j];
        }
    }
}

void Sudoku::eraseBoard(int (&board)[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = 0;
        }
    }
}

void Sudoku::eraseList(BoardState *&head)
{
    BoardState *traverser = head;
    while (traverser != NULL)
    {
        BoardState *tmp = traverser;
        traverser = traverser->next;
        delete tmp;
    }
    head = NULL;
}

void Sudoku::printList(BoardState *head)
{
    BoardState *traverser = head;
    int count = 0;
    while (traverser != NULL)
    {
        cout << "--------------------" << endl;
        cout << "Board count: " << count << endl;
        cout << "--------------------" << endl;
        printBoard(traverser->board);
        traverser = traverser->next;
        count++;
    }
}
