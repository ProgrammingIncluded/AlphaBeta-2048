/******************************************
 * Project: MCT-TFE
 * File: ABNode.hpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

#include <vector>
#include <random>
#include <algorithm>
#include <climits>

#include "types_macros.hpp"
#include "grid_util.hpp"

class ABNode {
    public:
        uint option;
        ABNode *parent;

        std::vector<ABNode *> children;
        std::vector<uint> children_options;

        uint total_games;
        uint total_wins;
        uint *grid;
        long long int val;
        long long int alpha;
        long long int beta;
        bool isTrav;
        bool isDirOnly;

        // NOTE: Grid is not copied.
        ABNode(ABNode *parent, uint option, uint *grid, bool isDirOnly = false);
        
        // Grid guranteed to be deleted.
        ~ABNode();

        /**
         * Create a child node.
         */
        ABNode* createChild();

    private:
        /**
         * Encode future grid orientations by unique id.
         */
        void genOpt();

        /**
         * Encode next layer as direction only.
         */
        void genDirOpt();

        /**
         * Decode unique option id to a grid orientation.
         */
        uint * optToGrid(uint opt);

        /**
         * Generates heuristic values from grid orientation.
         */
        long long int valueFromGrid(uint *A);

        // Make copy private so no one makes instance.
        ABNode(const ABNode &other) = delete;
};