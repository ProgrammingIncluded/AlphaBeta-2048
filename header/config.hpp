#pragma once

/******************************************
 * Project: MCT-TFE
 * File: config.hpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

#include <map>

#include "types_macros.hpp"

extern uint MONTE_CARLO;

// Grid is always square.
extern const uint GRID_WIDTH;
extern const uint GRID_SIZE;

// Win requirement
extern uint WIN_REQ;

// Heuristics
extern bool VAL_H;
extern long long int LEAF_WEIGHT;
extern double UCB_COEFF;

// Directions
extern char DIR[4];
extern uint DIR_SIZE;
extern std::map<char, int> DIR_TO_NUM;