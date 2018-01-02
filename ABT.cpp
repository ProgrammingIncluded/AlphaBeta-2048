#include "ABT.hpp"

/******************************************
 * Project: ABT-TFE
 * File: ABT.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

ABT::ABT(TFE &tfe) {
    // Need to make a copy for grid.
    root = new ABNode(nullptr, -1, copy_grid(tfe.getGrid()));
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

char ABT::run(float sec, bool noNone) {
    time_t start = time(0);
    float timeLeft = sec;

    while(timeLeft > 0 || noNone) {
        std::vector<ABNode*> trav;
        ABNode *curNode = forwardPropagate(root, trav, timeLeft, noNone); 
        
        timeLeft = sec - (time(0) - start);
        if(timeLeft <= 0 && !noNone)
            break;

        if(max_grid(curNode->grid) == WIN_REQ)
            backPropagate(trav, 1);
        else
            backPropagate(trav, 0);

        // Check if all children for root. If so, we can toggle noNone.
        if(root->children_options.size() == 0)
            noNone = false;

        timeLeft = sec - (time(0) - start);
    }

    if(root->children_options.size() != 0) {
        std::cout << "Not Enough Time." << std::endl;
        return 'E';
    }

    ABNode *highest = getHighestUCB(root->children);
    uint opt = highest->option;
    uint z = opt / (GRID_SIZE * DIR_SIZE);
    opt -= z * GRID_SIZE * DIR_SIZE;
    return DIR[opt % DIR_SIZE];
}

ABNode* ABT::forwardPropagate(ABNode *root, std::vector<ABNode*> &trav, float timeLeft, bool noNone) {
    ABNode *curNode = root;

    time_t start = time(0);
    float sec = timeLeft;
    while(timeLeft > 0 || noNone) {
        // Check if win node.
        if(max_grid(curNode->grid) == WIN_REQ)
            break;
    
        ABNode *res = curNode->createChild();

        if(res == nullptr) {
            // Check if Leaf Node
            if(curNode->children.size() == 0 && curNode->children_options.size() == 0) {
                // We can turn off our obligation to reach ending.
                noNone = false;
                break;
            }

            trav.push_back(curNode);
            curNode = getHighestUCB(curNode->children);
        }
        else {
            trav.push_back(res);
            curNode = res;
        }

        // Calculate time.
        time_t end = time(0);
        timeLeft = sec - (end - start);
    }

    // Save last node.
    trav.push_back(curNode);
    return curNode;
}

void ABT::backPropagate(std::vector<ABNode*> &trav, long long int win) {
    long long int accum = 0;

    while(trav.size() != 0) {
        ABNode *n = trav.back();
        trav.pop_back();

        n->total_games += 1;
        n->total_wins += win;

        accum += n->val;

        // Propagate UCB
        if(n->parent != nullptr) {
            n->UCB = UCB_COEFF * sqrt(log(n->parent->total_games + 1) / n->total_games); 
            
            // Update heuristics
            if(VAL_H) {
                n->val = accum;
                n->UCB += ((double) accum) / 1000000;
    
                // Update siblings
                for(auto s : n->parent->children)
                    s->UCB = (((double) s->val) / 1000000) + UCB_COEFF * sqrt(log(s->parent->total_games + 1) / s->total_games);
            }
            else {
                n->UCB += (n->total_wins/n->total_games);

                for(auto s : n->parent->children)
                    s->UCB = (s->total_wins/s->total_games) + UCB_COEFF * sqrt(log(s->parent->total_games + 1) / s->total_games);
            }
        }
    }
}

ABNode* ABT::getHighestUCB(std::vector<ABNode*> &children) {
    ABNode *res = nullptr;
    double selVal = LLONG_MIN;

    for(auto c : children) {
        if(selVal <= c->UCB) {
            res = c;
            selVal = c->UCB;
        }
    }

    return res;
}