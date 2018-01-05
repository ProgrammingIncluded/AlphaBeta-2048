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
    // Depth first search delete.
    std::vector<ABNode*> stack;
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

void ABT::boardUpdate() {
    
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