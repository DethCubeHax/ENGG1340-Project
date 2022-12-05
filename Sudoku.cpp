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
        cout << "Type [ exit ] to quit" << endl;
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
        else if (choice =="exit"){
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
    if (isSolved(board)) 
    {
        choice = "4";
        return 0;
    }
    printBoard(board);
    cout << "" << endl;
    string control;
    cin >> control;
    toLowerCase(control);
    if (control == "exit"){
        return 5;
    }
    if (control.length() > 1)
    {
        return 2;
    }
    if (control == "w" || control == "a" || control == "s" || control == "d"){
        cursorInputHandler(control);
        return 0;
    }
    if (stoi(control) == 0)
    {
        if(playerBoardHead->board[cursorY][cursorX] != 0)
        {
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
        if (playerBoardHead->board[cursorY][cursorX] != 0)
        {
            return 4;
        }
        board[cursorY][cursorX] = stoi(control);
        addToList(playerBoardHead, board);
        return 0;
    }
}

void Sudoku::finalScreen(int (&board)[SIZE][SIZE]){
    if (choice == "4"){
        cout << "Congratulations! You have solved the puzzle!" << endl;
        cout << "------------------------------------------" << endl;
        printBoard(board);
        cout << "------------------------------------------" << endl;
        cout << "Your time is: " << timeSinceBoot() - runTime << " milliseconds." << endl;
        cout << "Would you like to review your steps? (y/n)" << endl;
        string control;
        cin >> control;
        while(control.length() > 1 || (control != "y" && control != "n")){
            cout << "Invalid input. Please enter: [ y n ]." << endl;
            cin >> control;
        }
        if (control == "y"){
            printList(playerBoardHead, computerBoardHead);
        }
        else{
            cout << "Thank you for playing!" << endl;
        }
    }
    else{
        cout << "You have quit the game." << endl;
        choice = "exit";
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
    
    cout << "============= Instruction ===============" << endl;
    cout << "\nWelcome to sudoku! The objective of this\n";
    cout << "game is to fill a 9 × 9 grid with digits\n";
    cout << "so that each column, each row, and each\n";
    cout << "of the nine 3 × 3 subgrids that compos\n";
    cout << "the grid contain all of the digits from\n";
    cout << "1 to 9.\n\n";
    cout << "Controls:\n";
    cout << "The cursor X shows your current position.\n\n";
    cout << "W -> Move up one block\n";
    cout << "A -> Move left one block\n";
    cout << "S -> Move down one block\n";
    cout << "D -> Move right one block\n\n";
    cout << "Press enter after every move, then insert\n";
    cout << "a number.\n\n";


    cout << "=========================================" << endl;
    cout << "Press Enter to continue" << endl;
    cout << "=========================================" << endl;
    // cin.ignore();
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    choice = "";
    
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

void Sudoku::printList(BoardState *playerHead, BoardState *computerHead)
{
    BoardState *playerTraverser = playerHead;
    BoardState *computerTraverser = computerHead;;
    int count = 0;
    while (playerTraverser != NULL || computerTraverser != NULL)
    {
        cout << "--------------------" << endl;
        cout << "Your move number " << count << " :" << endl;
        cout << "--------------------" << endl;
        printBoard(playerTraverser->board);
        playerTraverser = playerTraverser->next;
        cout << "--------------------" << endl;
        cout << "Computer move number " << count << " :" << endl;
        cout << "--------------------" << endl;
        printBoard(computerTraverser->board);
        computerTraverser = computerTraverser->next;
        cout << "--------------------" << endl;
        cout << "Press enter to continue" << endl;
        cout << "--------------------" << endl;
        cin.ignore();
        count++;
    }
}

bool Sudoku::isSolved(int (&board)[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}
