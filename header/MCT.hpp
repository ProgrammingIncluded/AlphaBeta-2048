#pragma once

/******************************************
 * Project: MCT-TFE
 * File: MCT.hpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

#include <math.h>
#include <float.h>
#include <time.h>

#include "TFE.hpp"
#include "MCTNode.hpp"

class MCT {
    MCTNode *root;

    public:
        MCT(TFE &tfe);
        ~MCT();

        char run(float sec, bool noNone = false);

        MCTNode* forwardPropagate(MCTNode *root, std::vector<MCTNode*> &trav, float timeLeft, bool noNone);
        void backPropagate(std::vector<MCTNode*> &trav, long long int win);
        MCTNode* getHighestUCB(std::vector<MCTNode*> &children);
    
    private:
        MCT(const MCT &other) = delete;
};