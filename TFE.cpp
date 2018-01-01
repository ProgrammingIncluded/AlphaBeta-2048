#include "TFE.hpp"

/******************************************
 * Project: MCT-TFE
 * File: TFE.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/


TFE::TFE() {
    grid = new uint[GRID_SIZE]();
}

TFE::~TFE() {
    delete[] grid;
}

TFE::TFE(const TFE &other) {
    this->grid = copy_grid(other.grid);
}

void TFE::display() {
    print_grid(grid);
}

void TFE::move(char dir) {
    move_grid(grid, dir);
}

bool TFE::putNew() {
    auto cells = get_cells_where(grid, 0);
    if(cells.size() == 0)
        return false;

    int randNumber = 0;
    if(cells.size() > 1)
        randNumber = rand() % (cells.size() - 1);

    uint loc = cells[randNumber];

    // Set the value
    randNumber = (rand() % 100) + 1;
    if(randNumber > 10)
        grid[loc] = 2;
    else
        grid[loc] = 4;
    
    return true;
}

std::vector<std::pair<char, uint *>> TFE::availDir() {
    return avail_dir(grid);
}

bool TFE::isWin() {
    return (max_grid(grid) == WIN_REQ);
}

bool TFE::isLose() {
    std::vector<std::pair<char, uint*>> resVect = availDir();
    // Check size
    bool res = (resVect.size() == 0);
    
    // Clean up
    for(uint x = 0; x < resVect.size(); ++x)
        delete[] resVect[x].second;

    return res;
}