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
    ABNode *cur_root;

    public:
        ABT(TFE &tfe);
        ~ABT();

        char run();

        // Go down one level
        void boardUpdate(char dir, uint *gameGrid);

    private:
        ABT(const ABT &other) = delete;

        ABNode* getBestVal(std::vector<ABNode*> &children, bool isAlpha);

        // Basic alpha-beta implementation
        long long int alphaBeta(ABNode *node, uint depth, long long int A, long long int B);
};