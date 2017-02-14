//
//  sim_board.hpp
//  Simacogo
//
//  Created by Clayton Newmiller on 1/25/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#ifndef sim_board_hpp
#define sim_board_hpp

#include <stdio.h>

class SimBoard{
private:
    
    int board[9][9];//column, row
    int columnCounts[9];
    
public:
    enum slotValues{empty=0, player1=1, player2=2};
    SimBoard();
    SimBoard(SimBoard*);
    void printBoard();
    SimBoard* placeToken(int column, int player);
    int scoreBoard(slotValues player);
    int scoreSlot(int, int, slotValues);
    
    //A more efficient way to score a move than scoring the whole board
    int scoreSinglePlay(int,slotValues);
    
    bool operator==(const SimBoard& rightSide);
    
};


#endif /* sim_board_hpp */
