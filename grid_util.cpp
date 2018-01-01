#include "grid_util.hpp"

/**
 * Returns a copy of the grid.
 */
uint* copy_grid(uint *A){
    uint *ret = new uint[GRID_SIZE];
    std::memcpy(ret, A, sizeof(uint) * GRID_SIZE);
    return ret;
}

/**
 * Basic single element multiplication.
 * Dimensions assumed GRID_WIDTH in config.
 */
void mult_grid(uint *A, uint *B) {
    for(unsigned int x = 0; x < GRID_SIZE; ++x)
        A[x] = A[x] * B[x];
}

/**
 * Get the cells with value equal to given val.
 * Returns a vector of cell locations, linearly.
 */
std::vector<uint> get_cells_where(uint *A, uint val) {
    std::vector<uint> res;
    for(uint x = 0; x < GRID_SIZE; ++x)
        if(A[x] == val)
            res.push_back(x);
    
    return res;
}

void move_cell(uint *A, int x, int y, char dir) {
    // Check zero
    if(AC(A, x, y) == 0)
        return;

    // Check boundary cases
    if(x <= 0 && dir == 'l')
        return;
    else if(x >= 3 && dir == 'r')
        return;
    else if(y <= 0 && dir == 'u')
        return;
    else if(y >= 3 && dir == 'd')
        return;

    int xval, yval;

    // Direction checking.
    if(dir == 'l'){ xval = -1; yval = 0; }
    else if(dir == 'r'){ xval = 1; yval = 0; }
    else if(dir == 'd'){ xval = 0; yval = 1; }
    else{ xval = 0; yval = -1; }

    int dx = x + xval;
    int dy = y + yval;
    for(;;) {
        // Edit condition switch.
        if(dir == 'l') { if(dx < 0) break;}
        else if(dir == 'r') { if(dx >= 4) break;}
        else if(dir == 'd') { if(dy >= 4) break;}
        else { if(dy < 0) break ;}

       if(AC(A, dx, dy) == 0) {
           dx += xval; dy += yval;
       }
       else if(AC(A, dx, dy) == AC(A, x, y)) {
            AC(A,dx, dy) *= 2;
            AC(A, x, y) = 0;
            return;
       }
       else {
           break;
       }
    }

    AC(A, dx-xval, dy-yval) = AC(A, x, y);
    if((dy - yval != y) || (dx - xval != x))
        AC(A, x, y) = 0;
}

// Ugly, yes. Could I use lambdas? Probably
// But it works for now...
void move_grid(uint *A, char dir) {
    if(dir == 'l') {
        int x = 0, y = 0;
        int dy = y;
        while(dy < (int) GRID_WIDTH) {
            int dx = x;
            while(dx < (int) GRID_WIDTH) {
                move_cell(A, dx, dy, dir);
                ++dx;
            }
            ++dy;
        }
    }
    else if(dir == 'r') {
        int x = (int) GRID_WIDTH - 1, y = (int) GRID_WIDTH - 1;
        int dy = y;
        while(dy >= 0) {
            int dx = x;
            while(dx >= 0) {
                move_cell(A, dx, dy, dir);
                --dx;
            }
            --dy;
        }
    }
    else if(dir == 'd') {
        int x = (int) GRID_WIDTH - 1, y = (int) GRID_WIDTH - 1;
        int dx = x;
        while(dx >= 0) {
            int dy = y;
            while(dy >= 0) {
                move_cell(A, dx, dy, dir);
                --dy;
            }
            --dx;
        }
    }
    else {
        int x = 0, y = 0;
        int dx = x;
        while(dx < (int) GRID_WIDTH) {
            int dy = y;
            while(dy < (int) GRID_WIDTH) {
                move_cell(A, dx, dy, dir);
                ++dy;
            }
            ++dx;
        }
    }
}

// Check if grids are equal 
bool is_equal(uint *A, uint *B) {
    for(uint x = 0; x < GRID_SIZE; ++x)
        if(A[x] != B[x])
            return false;
    return true;
}

/**
 * Find max element in the grid.
 */
uint max_grid(uint *grid) {
    uint max = 0;
    for(uint x = 0; x < GRID_SIZE; ++x)
        if(grid[x] > max)
            max = grid[x];
    return max;
}

/**
 * Print the grid
 */
void print_grid(uint *A) {
    for(uint y = 0; y < GRID_WIDTH; ++y) {
        for(uint x = 0; x < GRID_WIDTH; ++x) {
            std::cout << std::setw(5);
            std::cout << AC(A, x, y);
            std::cout << std::setw(5);
        }
        std::cout << std::endl;
    }
}

std::vector<std::pair<char, uint *>> avail_dir(uint *grid) {
    std::vector<std::pair<char, uint *>> res;
    // If empty, we can take any direction
    if(max_grid(grid) == 0) {
        // Call memcpy only once.
        for(uint x = 0; x < DIR_SIZE; ++x) {
            uint *val = copy_grid(grid);
            res.push_back(std::pair<char, uint *>(DIR[x], val));
        }
        return res;
    }

    // Try moving our values.
    for(uint x = 0; x < DIR_SIZE; ++x) {
        uint *val = copy_grid(grid);
        move_grid(val, DIR[x]);

        // check if same
        if(is_equal(val, grid)){
            delete[] val;
            continue;
        }
        // Not the same, add it to result.
        res.push_back(std::pair<char, uint *>(DIR[x], val));
    }

    return res;
}

void rotate_grid_90(uint *A) {
    uint n = GRID_WIDTH;
    for(uint i = 0; i < n/2; ++i) {
        for(uint j = 0; j < (n + 1)/2; ++j) {
            uint temp = AC(A, i, j);
            AC(A, i, j) = AC(A, n - 1 - j, i);
            AC(A, n - 1 - j, i) = AC(A, n - 1 - i, n - 1 - j);
            AC(A, n - 1 - i, n - 1 - j) = AC(A, j, n - 1 - i);
            AC(A, j, n - 1 - i) = temp;
        }
    }
}

long long int* diff_grid(uint *A) {
    long long int* res = new long long int[(GRID_WIDTH) * (GRID_WIDTH - 1)]();

    for(uint y = 0; y < GRID_WIDTH; ++y){
        for(uint x = 0; x < GRID_WIDTH - 1; ++x) {
            res[x + y * (GRID_WIDTH - 1)] = ((long long int) AC(A, x + 1, y)) - ((long long int) AC(A, x, y));
        }
    }

    return res;
}

void clip(long long int* A, long long int min, long long int max, uint size) {
    for(uint x = 0; x < size; ++x) {
        if(A[x] < min)
            A[x] = min;
        else if(A[x] > max)
            A[x] = max;
    }
}

long long int sum(long long int* A, uint size) {
    long long int res = 0;
    for(uint x = 0; x < size; ++x)
        res += (long long int) A[x];

    return res;
}