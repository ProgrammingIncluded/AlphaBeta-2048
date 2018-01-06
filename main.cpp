/******************************************
 * Project: ABT-TFE
 * File: main.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>

#include "TFE.hpp"
#include "ABT.hpp"
#include "grid_util.hpp"

int main() {
    // Init seed with nanosecond time.
    std::srand(time(NULL));

    TFE tfe;
    tfe.putNew();
    tfe.putNew();
    std::cout << "STARTING BOARD: " << std::endl;
    tfe.display();
    std::cout << std::endl;
    
    ABT abt(tfe);
    while(!tfe.isWin() && !tfe.isLose()) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::cout << "*********************" << std::endl;
        char act = abt.run();
        std::cout << "AI SELECT ACTION: " << act << std::endl;
        std::cout << "*********************" << std::endl;
        std::cout << "BEFORE: " << act << std::endl;
        tfe.display();
        std::cout << std::endl;

        std::cout << "*********************" << std::endl;
        std::cout << "AFTER: " << act << std::endl;

        tfe.move(act);

        tfe.putNew();

        tfe.display();
        std::cout << std::endl;

        // Update the alpha-beta ai.
        abt.boardUpdate(act, tfe.getGrid());

        std::cout << "TIME TAKEN FOR STEP: ";
        // Print seconds
        std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
        std::cout << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 <<std::endl;
    }
    
    std::cout << "FINISHED: " << std::endl;
    tfe.display();
    std::cout << std::endl;

    std::cout << "IS WIN?: " << std::endl;
    std::cout << tfe.isWin() << std::endl;
    std::cout << std::endl;

    std::cout << "IS LOSE?: " << std::endl;
    std::cout << tfe.isLose() << std::endl;
    std::cout << std::endl;
}