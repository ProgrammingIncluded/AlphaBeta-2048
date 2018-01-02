#pragma once

/******************************************
 * Project: ABT-TFE
 * File: ABT.hpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

#include <math.h>
#include <float.h>
#include <time.h>

#include "TFE.hpp"
#include "ABNode.hpp"

class ABT {
    ABNode *root;

    public:
        ABT(TFE &tfe);
        ~ABT();

        char run(float sec, bool noNone = false);

        ABNode* forwardPropagate(ABNode *root, std::vector<ABNode*> &trav, float timeLeft, bool noNone);
        void backPropagate(std::vector<ABNode*> &trav, long long int win);
        ABNode* getHighestUCB(std::vector<ABNode*> &children);
    
    private:
        ABT(const ABT &other) = delete;
};