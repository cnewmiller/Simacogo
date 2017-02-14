//
//  adversary.hpp
//  Simacogo
//
//  Created by Clayton Newmiller on 1/27/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#ifndef adversary_hpp
#define adversary_hpp

#include <stdio.h>
#include "min_max_node.hpp"

class Adversary{
    
private:
    
    Node* rootNode;
    
public:
    Adversary(SimBoard*);
    
    SimBoard* makeMove(SimBoard*, int, SimBoard::slotValues);
    SimBoard* makeMoveAlphaBeta(SimBoard*, int, SimBoard::slotValues);
    
    
};


#endif /* adversary_hpp */
