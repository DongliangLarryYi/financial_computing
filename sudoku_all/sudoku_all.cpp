//  Sudoku Solver via exhaustive search using recursion
//  Created by Dongliang Yi on 9/14/15.
//  Copyright (c) 2015 Dongliang Yi. All rights reserved.

#include <iostream>
#include "sudoku_all.h"

int main (int argc, char * const argv[])
{
    Sudoku x;
    x.read_puzzle(argc, argv);
    x.print_puzzle();
    x.Solve(0,0);
    x.print_total();
    return 0;
}
