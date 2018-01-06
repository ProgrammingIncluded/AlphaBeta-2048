#include "ABT.hpp"

/******************************************
 * Project: ABT-TFE
 * File: ABT.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

ABT::ABT(TFE &tfe) {
    // Need to make a copy for grid.
    root = new ABNode(nullptr, -1, copy_grid(tfe.getGrid()), true);
    cur_root = root;
}

ABT::~ABT() {
    deleteTree(root);
}

void ABT::deleteTree(ABNode *node) {
    // Depth first search delete.
    std::vector<ABNode*> stack;
    stack.push_back(node);
    while(!stack.empty()) {
        ABNode *cur = stack.back();
        stack.pop_back();
        // Add the children
        for(auto c : cur->children)
            stack.push_back(c);

        // Delete the node which deletes the grid.
        delete cur;
    }
}

char ABT::run() {
    alphaBeta(this->cur_root, MAX_DEPTH, LLONG_MIN, LLONG_MAX);

    ABNode* highest = getBestVal(cur_root->children, true);
    uint opt = highest->option;
    return DIR[opt];
}

void ABT::boardUpdate(char dir, uint *gameGrid) {
    // Get the direction of the move. Go down that path.
    ABNode *trav = cur_root;
    // Go down the direction
    uint dirNum = DIR_TO_NUM[dir];
    for(auto c : trav->children) {
        if(c->option == dirNum) {
            trav = c;
            break;
        }
    }
    
    // Delete other directions
    for(auto c : root->children) {
        if(c == trav)
            continue;
        this->deleteTree(c);
    }
    // Update root
    delete root;
    root = trav;

    uint pos = one_change_grid(trav->grid, gameGrid);
    uint val = gameGrid[pos];

    // Find the option encoding.
    uint valBool = 0;
    if(val == 4)
        valBool = 1;

    uint opt = pos + GRID_SIZE * valBool;

    ABNode* n = trav->createChild(opt);
    // Node does not exist, was created 
    if(n != nullptr) {
        cur_root = n;
    }
    else {
        // Node does exist, find it in the board.
        // Find the node.
        for(auto c : trav->children) {
            if(c->option == opt) {
                cur_root = c;
                break;
            }
        }
    }
    
    // Clear up all the other branches.
    for(auto c : root->children) {
        if(c == cur_root)
            continue;
        this->deleteTree(c);
    }

    delete root;
    root = cur_root;

}

ABNode* ABT::getBestVal(std::vector<ABNode*> &children, bool isAlpha) {
    ABNode *res = nullptr;
    long long int selVal = LLONG_MIN;

    for(auto c : children) {
        if(isAlpha && selVal <= c->alpha) {
            res = c;
            selVal = c->alpha;
        }
        else if(!isAlpha && selVal >= c->beta) {
            res = c;
            selVal = c->beta;
        }
    }

    return res;
}

long long int ABT::alphaBeta(ABNode *node, uint depth, long long int A, long long int B) {
    if(depth == 0 || node->children_options.size() == 0)
        return node->val;
    
    if(node->isDirOnly) {
        long long int v = LLONG_MIN;
        for(;;) {
            ABNode *cur = node->createChild();
            if(cur == nullptr)
                break;
            
            if(cur->isTrav) {
                std::cout << "SKIPPING" << std::endl;
                A = cur->alpha;
                continue;
            }

            v = std::max(v, alphaBeta(cur, depth - 1, A, B));
            A = std::max(v, A);
            cur->alpha = A;
            cur->isTrav |= true;

            if(B <= A)
                break;
        }
        return v;
    }

    long long int v = LLONG_MAX;
    for(;;) {
        ABNode *cur = node->createChild();
        if(cur == nullptr)
            break;
        
        if(cur->isTrav) {
            std::cout << "SKIPPING" << std::endl;
            B = cur->beta;
            continue;
        }

        v = std::min(v, alphaBeta(cur, depth - 1, A, B));
        B = std::min(v, B);
        cur->beta = B;
        cur->isTrav |= true;

        if(B <= A)
            break;
        
    }
    return v;
}