#include "config.hpp"

uint MONTE_CARLO = 0;

const uint GRID_WIDTH = 4;
const uint GRID_SIZE = GRID_WIDTH * GRID_WIDTH;

uint WIN_REQ = 2048;
bool VAL_H = true;
double UCB_COEFF = 1.2;
long long int LEAF_WEIGHT = 1000;

char DIR[4] = {'u', 'd', 'l', 'r'};
uint DIR_SIZE = 4;
std::map<char, int> DIR_TO_NUM = {{DIR[0], 0}, {DIR[1], 1}, {DIR[2], 2}, {DIR[3], 3}};
