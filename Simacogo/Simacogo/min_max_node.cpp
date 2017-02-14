//
//  min_max_node.cpp
//  Simacogo
//
//  Created by Clayton Newmiller on 1/26/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#include "min_max_node.hpp"
#include <algorithm>

/*
 Public constructor for the root node
 */
Node::Node(SimBoard* init, SimBoard::slotValues computerPlayer){
    state = init;
    depth=0;
    isMaxNode=true;
    playerToPlace = computerPlayer;
    
    if (computerPlayer == SimBoard::player1) oppositePlayer = SimBoard::player2;
    else oppositePlayer = SimBoard::player1;
    
    
    value=0;
    moveToHere=-1;
    expanded=false;
    playerToScore=computerPlayer;
}

/*
 Private constructor for expansion
 */
Node::Node(SimBoard* paramState, Node* parent){
    parent_node = parent;
    state=paramState;
    depth=parent_node->depth+1;
    isMaxNode = !(parent->isMaxNode);
    
    if (parent->playerToPlace==SimBoard::player1){
        playerToPlace=SimBoard::player2;
    }
    else{
        playerToPlace=SimBoard::player1;
    }
    playerToScore=parent->playerToScore;
    oppositePlayer=parent->oppositePlayer;
    
    
    expanded=false;
}
/*
 Destructor, percolates downwards
 */
Node::~Node(){
    for (int i=0;i<9;i++){
        if (expanded && children[i]!=nullptr && children[i] != NULL){
            delete(children[i]);
        }
    }
    delete(state);
}

/*
 Sucessor function; expands a node. No repeated state checking, because each state builds off the previous one, but will
 not build a child if the column is full
 Sets the value of the child node
 */
void Node::expand(){
    expanded=true;
    for (int i=0;i<9;i++){
        children[i]=new Node(state->placeToken(i, playerToPlace), this);
        children[i]->moveToHere = i;
        if (*(children[i]->state) == (*state)){
            delete children[i];
            children[i]=nullptr;
            continue;
        }
        
        //sets the child's value
        if (playerToPlace == playerToScore){
            children[i]->value=value+children[i]->state->scoreSinglePlay(i, playerToPlace);
        }
        else
            children[i]->value=value-children[i]->state->scoreSinglePlay(i, playerToPlace);
        
    }
}




/*
Does alpha-beta pruned Minimax to get the best choice. replaces the parent node's value with the best (min or max, depending on isMaxNode) child's value, and records the parent node's choice of where that value came from in moveChoice
 */
Node* Node::getBestChild(int ply){
    
    this->alpha = parent_node->alpha;
    this->beta = parent_node->beta;
    if (depth == ply){
        return this;
    }
    
    if (!expanded){
        expand();
    }
    
    Node* bestNode=nullptr;
    
    if (isMaxNode){ //max node, look for max child value
        for (int i=0;i<9;i++){
            if (children[i]!=nullptr || children[i] !=NULL){
                
                Node* currentNode = children[i]->getBestChild(ply);
                
                if (bestNode==nullptr || currentNode->value > bestNode->value){
                    //percolates best value upward
                    value=currentNode->value;
                    
                    //keeps track of which node was the best choice
                    bestNode = currentNode;
                    
                    //keeps track of the move needed to get to that node
                    moveChoice=i;
                }
                
                //alpha-beta pruning
                alpha = std::max(alpha, bestNode->value);
                if (beta<=alpha)break;
                
            }
        }
    }
    else{ //min node, look for min child value
        for (int i=0;i<9;i++){
            if (children[i]!=nullptr){
                Node* currentNode = children[i]->getBestChild(ply);
                if (bestNode==nullptr || currentNode->value < bestNode->value){
                    value=currentNode->value;
                    bestNode = currentNode;
                    moveChoice=i;
                }
                beta = std::min(beta, bestNode->value);
                if (beta<=alpha) break;
                
            }
        }
    }
    return this;
}



