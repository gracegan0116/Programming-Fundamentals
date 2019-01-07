//
//  playMove.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <tic-tac-toe/playMove.h>

using namespace std;

void playMove(int board[3][3], int row, int col, bool& turn, bool& validMove, bool& gameOver, int& winCode) {

    // If the game is over, do nothing
    if (gameOver) return;

    // Insert your code here
    
    //Check if move is valid
    if (board[row][col] == 0){
        validMove = true;
        if (turn){
            board[row][col] = 1;
            turn = !turn;
        }
        else{
            board[row][col] = -1;
            turn = !turn;
        }
    }
    else{
        validMove = false;
    }
    
    //Check if game is over (gameOver)
    //Check for win
    //Horizontal
    for (int x=0; x<3; x++){
        for (int y=0; y<1; y++){
            if (board[x][y]!=0){
                if (board[x][y] == board[x][y+1] && board[x][y] == board[x][y+2]){
                    gameOver = true;
                    winCode = x+1;
                }
            }
        }
    }
    //Vertical
    for (int y=0; y<3; y++){
        for (int x=0; x<1; x++){
            if (board[x][y]!=0){
                if (board[x][y] == board[x+1][y] && board[x][y] == board[x+2][y]){
                    gameOver = true;
                    winCode = y+4;
                }
            }
        }
    }
    //Diagonal from top left to bottom right
    for (int x=0, y=0; x<1 && y<1; x++,y++){
        if ((1 == board[x][y] && 1 == board[x+1][y+1] && 1 == board[x+2][y+2])||
            (-1 == board[x][y] && -1 == board[x+1][y+1] && -1 == board[x+2][y+2])){
            gameOver = true;
            winCode = 7;
        }
    }
    
    //Diagonal from top right to bottom left
    for (int x=2, y=0; x>=2 && y>=0; x--,y--){
        if ((1 == board[x][y] && 1 == board[x-1][y+1] && 1 == board[x-2][y+2])||
            (-1 == board[x][y] && -1 == board[x-1][y+1] && -1 == board[x-2][y+2])){
            gameOver = true;
            winCode = 8;
        }
    }
    //Check for draw
    if (gameOver != true){
        bool empty;
        for (int x=0; x<3; x++){
            for (int y=0; y<3; y++){
                if (board[x][y] == 0){
                    empty = true;
                }
            }
        }
        if(empty){
            gameOver = false;
            winCode = 0;
        }
        else{
            gameOver = true;
            winCode = 0;
        }
    }

    // The function must always print the output specified in the handout before it exits
    // Use the standard output (i.e., cout) to print the output

    // Insert code to print the output below
    //printing the game board array
    for (int x = 0; x<3; x++){
        for (int y=0; y<3; y++){
            cout << board[x][y] << " ";
        }
    }
    //printing other descriptive variables
    cout << row << " "<< col << " " << turn << " " << validMove << " "<< gameOver<< " " << winCode << endl;
}

