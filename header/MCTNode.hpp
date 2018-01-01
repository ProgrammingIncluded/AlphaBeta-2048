/******************************************
 * Project: MCT-TFE
 * File: MCTNode.hpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

#include <vector>
#include <random>

#include "types_macros.hpp"
#include "grid_util.hpp"

class MCTNode {
    public:
        uint option;
        MCTNode *parent;

        std::vector<MCTNode *> children;
        std::vector<uint> children_options;

        uint total_games;
        uint total_wins;
        double UCB;
        uint *grid;
        long long int val;

        // NOTE: Grid is not copied.
        MCTNode(MCTNode *parent, uint option, uint *grid);
        
        // Grid guranteed to be deleted.
        ~MCTNode();

        /**
         * Create a child node.
         */
        MCTNode* createChild();

    private:
        /**
         * Encode future grid orientations by unique id.
         */
        void genOpt();

        /**
         * Decode unique option id to a grid orientation.
         */
        uint * optToGrid(uint opt);

        /**
         * Generates heuristic values from grid orientation.
         */
        long long int valueFromGrid(uint *A);

        // Make copy private so no one makes instance.
        MCTNode(const MCTNode &other) = delete;
};