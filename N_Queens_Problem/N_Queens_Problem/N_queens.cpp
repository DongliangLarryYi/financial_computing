//  main.cpp
//  N_Queens_Problem
//  Created by Dongliang Yi on 9/10/15.
//  Copyright (c) 2015 Dongliang Yi. All rights reserved.
// N Queens Problem via (Backtracking, which is implemented by) Recursion
// Written by Prof. Sreenivas for IE523: Financial Computing

#include <iostream>
#include "N_queens.h"

int main (int argc, char * const argv[])
{
    Board x;
    int board_size;
    sscanf (argv[1], "%d", &board_size); // command line input the N of the problem
    x.nQueens(board_size);
    return 0;
}
