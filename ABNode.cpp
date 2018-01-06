#include "ABNode.hpp"

/******************************************
 * Project: ABT-TFE
 * File: ABNode.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

ABNode::ABNode(ABNode *parent, uint option, uint *grid, bool isDirOnly) {
    this->parent = parent;
    this->option = option;
    this->grid = grid;
    this->total_games = 0;
    this->total_wins = 0;
    this->alpha = LLONG_MIN;
    this->beta = LLONG_MAX;
    this->isTrav = false;
    this->isDirOnly = isDirOnly;

    // Create children options, must call after grid is set
    if(!isDirOnly)
        genOpt();
    else {
        genDirOpt();
    }
        

    // Check to see if we should adjust value.
    if(VAL_H) {
        if(children_options.size() != 0)
            val = valueFromGrid(grid);
        else if(max_grid(grid) == WIN_REQ)
            val = LEAF_WEIGHT;
        else
            val = -LEAF_WEIGHT;
    }
}

ABNode::~ABNode() {
    delete[] grid;
}

ABNode* ABNode::createChild() {
    if(children_options.size() == 0)
        return nullptr;
    
    // Find a random child.
    int randNumber = 0;
    if(children_options.size() > 1)
        randNumber = rand() % (children_options.size() - 1);

    uint opt = children_options[randNumber];

    // Delete option
    children_options.erase(children_options.begin() + randNumber);
    
    uint *optGrid = optToGrid(opt);
    // Negate the direction only for next layer.
    ABNode* resNode = new ABNode(this, opt, optGrid, !isDirOnly);

    children.push_back(resNode);
    return resNode;
}

ABNode* ABNode::createChild(uint opt){
    // Find the value location.
    auto re = std::find(children_options.begin(), children_options.end(), opt);
    if(re == children_options.end())
        return nullptr;

    children_options.erase(re);
    
    uint *optGrid = optToGrid(opt);
    // Negate the direction only for next layer.
    ABNode* resNode = new ABNode(this, opt, optGrid, !isDirOnly);

    children.push_back(resNode);
    return resNode;
}

void ABNode::genDirOpt() {
    auto opt = avail_dir(this->grid);
    // Get available directions.
    for(auto i : opt) {
        children_options.push_back((uint) DIR_TO_NUM[i.first]);
    }

    // Clean up.
    for(auto i : opt)
        delete[] i.second;
}

uint * ABNode::optToGrid(uint opt) {
    // Options are simply direction encoded.
    if(this->isDirOnly) {
        uint *res = copy_grid(grid);
        move_grid(res, DIR[opt]);
        return res;
    }

    uint v = (uint) (opt / GRID_SIZE);
    uint loc = opt % GRID_SIZE;

    uint *res = copy_grid(grid);

    if(v == 0)
        res[loc] = 2;
    else
        res[loc] = 4;
    
    return res;
}

void ABNode::genOpt() {
    std::vector<uint> res;

    std::vector<uint> where = get_cells_where(this->grid, 0);
    for(uint i = 0; i < where.size(); ++i) {
        res.push_back(where[i]);
        res.push_back(where[i] + GRID_SIZE);
    }

    children_options = res;
}


long long int ABNode::valueFromGrid(uint *A) {
    long long int res = 0;
    uint *fil = copy_grid(A);

    // Size after difference
    uint size = (GRID_WIDTH - 1) * GRID_WIDTH;
    long long int *d = diff_grid(fil);
    clip(d, 0, 1, size);
    res += sum(d, size);
    delete[] d;
    
    // Rotate and do again.
    rotate_grid_90(fil);
    d = diff_grid(fil);
    clip(d, 0, 1, size);
    res += sum(d, size);
    delete[] d;

    delete[] fil;
    return res;
}