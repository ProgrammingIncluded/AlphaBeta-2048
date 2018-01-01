#pragma once

/******************************************
 * Project: MCT-TFE
 * File: TFE.hpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

#include <vector>
#include <utility>
#include <cstdlib>
#include <random>

#include "config.hpp"
#include "grid_util.hpp"
#include "types_macros.hpp"

// Note, the line between TFE and grid_util
// is slightly more blurry. Can be done
// more clearly. Add as TODO?
// Also, copy constructor copies grid in heap.
// For those who don't want that, make copy constructor private
// or use unique ptr.
class TFE {
    // Save grid as 1d array.
    uint *grid;

    public:
        // Constructor
        TFE();

        // Deconstructor
        ~TFE();

        // Copy constructor. Naively copies heap.
        TFE(const TFE &other);

        uint *getGrid() { return grid; }

        // Display the grid.
        void display();

        // Move the grid.
        void move(char dir);

        // Add a new item. True if successful.
        bool putNew();

        // Move All Directions and Return Results.
        std::vector<std::pair<char, uint *>> availDir();

        // Check if win. Linear to grid size.
        bool isWin();

        // Check if lose. WARNING: Is costly.
        // Since negation of NP-HARD check.
        // Don't use as much as possible.
        bool isLose();
};