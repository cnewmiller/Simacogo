
//  min_max_node.hpp
//  Simacogo
//
//  Created by Clayton Newmiller on 1/26/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#ifndef min_max_node_hpp
#define min_max_node_hpp

#include <stdio.h>
#include "sim_board.hpp"

class Node{
    
private:
    
    Node* parent_node;
    SimBoard* state;
    
    Node* children[9];
    
    int value, depth, moveToHere, moveChoice;
    
    int alpha= -50000, beta = 50000; //lazy replacement for infinity
    
    bool isMaxNode, expanded; //true is max, false is min
    
    //These are necessary to allow the computer to play itself
    SimBoard::slotValues playerToPlace; //alternates
    SimBoard::slotValues playerToScore; //stays the same
    SimBoard::slotValues oppositePlayer;//stays the same
    
    Node(SimBoard*, Node*);
    
public:
    Node(SimBoard*, SimBoard::slotValues);
    
    ~Node();
    
    
    Node* getBestChild(int);
    
    void expand();
    
    void setParent(Node* p){parent_node=p;};
    Node* getParent(){return parent_node;};
    
    int getMoveToHere(){return moveToHere;};
    int getMoveChoice(){return moveChoice;};
    int getValue(){return value;};
    int getDepth(){return depth;};
    void setValue(int val){value=val;};    
    void setPlayerToScore(SimBoard::slotValues player);
};


#endif /* min_max_node_hpp */
