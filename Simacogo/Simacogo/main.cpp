//
//  main.cpp
//  Simacogo
//
//  Created by Clayton Newmiller on 1/25/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#include <iostream>
#include "sim_board.hpp"
#include "adversary.hpp"
#include "min_max_node.hpp"

int main(int argc, const char * argv[]) {
    SimBoard s= SimBoard();
    Adversary player2(&s);
//    
    printf("Welcome to Simacogo!\nHow far ahead should I plan? I can go up to 10 easily, more than that and you'll need to wait a bit: ");
    int plys;
    std::cin>>plys;
//
    printf("Thank you! You go first... input the number of the column you want to play in...\n");
    int player1score=0, player2score=0;
    s.printBoard();
    for (int i=0;i<40;i++){ //player 1 is O
        
        int move;
        std::cin>>move;
        SimBoard temp = s.placeToken(move-1, 1);
        while (temp==s){
            printf("I'd be happy to let you play there, but you can't. Try again:");
            std::cin>>move;
            temp = s.placeToken(move-1, 1);
        }
        
        
        s = s.placeToken(move-1, 1);
        s = player2.makeMoveAlphaBeta(&s, plys, SimBoard::player2);
        s.printBoard();
        
        player1score = s.scoreBoard(SimBoard::slotValues::player1);
        player2score = s.scoreBoard(SimBoard::slotValues::player2);
        
        printf("score for player 1: %d\n", player1score);
        printf("score for player 2: %d\n", player2score);
        
    }
    
    if (player1score>player2score)
        printf("Congratulation. You're smarter than a homework project. I hope you feel good about yourself.\n");
    else
        printf("Good thing I'm not programmed for trash talk, loser.\n");
    
    
    return 0;
}
