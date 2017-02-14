//
//  sim_board.cpp
//  Simacogo
//
//  Created by Clayton Newmiller on 1/25/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#include "sim_board.hpp"

/*
 Initializes to 0s
 */
SimBoard::SimBoard(){
    for (int i=0;i<9;i++){
        for (int j=0;j<9;j++){
            board[i][j]=empty;
        }
        columnCounts[i]=0;
    }
}

/*
 Copy constructor
 */
SimBoard::SimBoard(SimBoard* copyFrom){
    for(int i=0;i<9;i++){
        for (int j=0;j<9;j++){
            board[i][j] = copyFrom->board[i][j];
        }
        columnCounts[i]=copyFrom->columnCounts[i];
    }
}
/*
 Compares boards
 */
bool SimBoard::operator==(const SimBoard& rightSide){
    for(int i=0;i<9;i++){
        for (int j=0;j<9;j++){
            if (board[i][j] != rightSide.board[i][j]) return false;
        }
    }
    return true;
}

/*
 Helper function prints the board with column counts
 */
void SimBoard::printBoard(){
    printf("-----------------------------------\n");
    for (int i=8;i>=0;i--){
        for (int j=0;j<9;j++){
            char play = ( board[i][j]==1 ? 'O' : 'X');
            if (board[i][j]==0) printf("|_ |");
            else printf("|_%c|",play);
        }
        
        printf("\n");
    }
    printf("-----------------------------------\n");
    for (int j=0;j<9;j++)
        printf(" %d |", j+1);
    printf("\n-----------------------------------\n");
}

/*
 Returns the board with the token dropped in the desired column
 */
SimBoard* SimBoard::placeToken(int column, int player){
    SimBoard* ret = new SimBoard(this);
    if (ret->columnCounts[column]<9)
        ret->board[ret->columnCounts[column]++][column]=player;
    return ret;
}

/*
 Counts the score for a given slot on the board for the given player
 */
int SimBoard::scoreSlot(int col, int row, SimBoard::slotValues player){
    if (player == empty || player != board[col][row]) return 0;
    
    int total=0;
    //check sides
    if (col>0){
        if ( board[col-1][row]==player) total +=2;
        if (row>0 && board[col-1][row-1]==player) total+=1;
        if (row<9 && board[col-1][row+1]==player) total+=1;
        
    }
    if (col<9){
        if (board[col+1][row]==player)total +=2;
        if (row>0 && board[col+1][row-1]==player) total+=1;
        if (row<9 && board[col+1][row+1]==player) total+=1;
    }
    //check top
    if (row>0 && board[col][row-1]==player) total +=2;
    if (row<9 && board[col][row+1]==player) total +=2;
    
    return total;
}

/*
 Scores entire board for a particular player
 */
int SimBoard::scoreBoard(SimBoard::slotValues player){
    int total=0;
    for (int i=8;i>=0;i--){
        for (int j=0;j<9;j++){
            if(board[i][j]==player) total+=scoreSlot(i, j, player);
        }
    }
    return total/2; //all points are counted twice, so the half is the single result
}

/*
 Score the most recent move in a column.
 */
int SimBoard::scoreSinglePlay(int columnPlayedIn, slotValues playerToScore){
    int score = scoreSlot(columnPlayedIn, columnCounts[columnPlayedIn]-1, playerToScore);
    return score;
}

