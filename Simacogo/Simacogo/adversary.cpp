//
//  adversary.cpp
//  Simacogo
//
//  Created by Clayton Newmiller on 1/27/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#include "adversary.hpp"

Adversary::Adversary(SimBoard* baseState){
}

/*
 Returns a pointer to a new SimBoard created by making the optimal calculated move
 */
SimBoard* Adversary::makeMoveAlphaBeta(SimBoard* playBoard, int ply, SimBoard::slotValues player){
    rootNode = new Node(new SimBoard(playBoard), player);
    rootNode->setParent(rootNode);
    Node* temp =rootNode->getBestChild(ply);
    int play = temp->getMoveChoice();
    SimBoard* ret = playBoard->placeToken(play, player);
    delete(rootNode);
    return ret;
}

