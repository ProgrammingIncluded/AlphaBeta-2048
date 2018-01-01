#pragma once

/******************************************
 * Project: MCT-TFE
 * File: matrix_util.h
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
 * Desc.: File to contain helpers for 
 *       grid manipulation.
*******************************************/

#include <vector>
#include <iostream>
#include <cstring>
#include <utility>
#include <iomanip>

#include "config.hpp"
#include "types_macros.hpp"

/** Grid Specific Utils **/
// These functions assume GRID_WIDTH and GRID_SIZE.

// Copy given grid and return new grid.
uint* copy_grid(uint *A);

// Multiply one grid with another. Element-wise multiplication.
void mult_grid(uint *A, uint *B);

// Gets cell index where val is given. Index is flattened.
std::vector<uint> get_cells_where(uint *A, uint val);

// Helper function for move_grid. Moves a single cell.
void move_cell(uint *A, int x, int y, char dir);

// Moves the entire grid a certain direction.
void move_grid(uint *A, char dir);

// Checks if two grids are equal.
bool is_equal(uint *A, uint *B);

// Gets the max element of the grid. Good for checking win state.
uint max_grid(uint *grid);

// Print the grid.
void print_grid(uint *A);

// Check available directions.
std::vector<std::pair<char, uint *>> avail_dir(uint *grid);

// Rotate the grid by 90 degrees.
void rotate_grid_90(uint *A);

// Get the difference matrix.
// Returns a new array of dim(GRID_WIDTH - 1, GRID_WIDTH)
long long int* diff_grid(uint *A);

/* Matrix Specific Functions */
// These functions require specific size of grid since not assumed.

// Clip values to max and min if they exceed.
void clip(long long int* A, long long int min, long long int max, uint size);

// Returns a summed number of the all the elements in the matrix.
long long int sum(long long int* A, uint size);