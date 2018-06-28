// A Sudoku Puzzle consists of a 9 × 9 grid, that is subdivided into nine 3 × 3
// blocks. Each entry in the grid must be filled with a number from {1, 2, . . . , 9},
// where some entries are already filled in. The constraints are that every number
// should occur exactly once in each row, each column, and each 3 × 3 block.
//  Created by Dongliang Yi on 9/14/15.
//  Copyright (c) 2015 Dongliang Yi. All rights reserved.

#ifndef sudoku_all
#define sudoku_all
#include <vector>
#include <fstream>
using std::vector;
using namespace std;
class Sudoku
{
    // declare private variables in the class 
    int puzzle[9][9];
    int count = 0;//this is used to count all solutions
    bool Remain_Zero_Check(int row, int col) // this is used to check whether there is any zero/blank field left.
    {
        for (int i = row; i <9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
             if( 0 == puzzle[i][j])
                 return true;
            }
        }
        return false;
    }
    // Private member function that checks if row is valid
    bool row_valid(int row, int col)
    {
        for (int x = 0; x <9; x++ )
        {
            if (x == col) {
            }
            else
                if (puzzle[row][col] == puzzle[row][x])
                {
                    return false;
                }
        }
        return true;
    }
    
    // Private member function that checks if column is valid
    bool col_valid(int row, int col)
    {
        for (int x = 0; x <9; x++ ) {
            if (x == row) {
            }
            else
                if (puzzle[row][col] == puzzle[x][col]) 
                {
                    return false;
                }
        }
        return true;
    }
    
    // Private member function that checks if 3x3 block is valid
    bool block_valid(int row, int col)
    {
        // condition on current row and col position
        if (0 == row && 0 == col)
        { 
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if ( i == row && j == col) 
                    {
                    }
                    else
                        if(puzzle[row][col] == puzzle[i][j]) // return false if duplicate
                            return false;
                }
            }
            
        }
        if (0 == row && 0 != col)
        {
            int inter1 = col/3;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 3*inter1; j < 3*inter1 + 3; j++)
                {
                    if ( i == row && j == col) 
                    {
                    }
                    else
                        if(puzzle[row][col] == puzzle[i][j])
                            return false;
                }
            }
        }
        if (0 == col && 0 != row)
        {
            int inter1 = row/3;
            for (int i = 3*inter1; i < 3*inter1+3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if ( i == row && j == col) 
                    {
                    }
                    else
                        if(puzzle[row][col] == puzzle[i][j])
                            return false;
                }
            }
        }
        if (0 != col && 0 != row)
        {
            int inter1 = row/3;
            int inter2 = col/3;
            for (int i = 3*inter1; i < 3*inter1+3; i++)
            {
                for (int j = 3*inter2; j < 3*inter2+3; j++)
                {
                    if ( i == row && j == col) 
                    {
                    }
                    else
                        if(puzzle[row][col] == puzzle[i][j])
                            return false;
                }
            }
        }
        return true;
    }
    
public:
    // Public member function that reads the incomplete puzzle
    // we are not doing any checks on the input puzzle -- that is,
    // we are assuming they are indeed valid
    void read_puzzle(int argc, char * const argv[])
    {
        ifstream input_file(argv[1]);
        int value_just_read_from_file;
        if (input_file.is_open()) // check whether txt file exists in the local directory
        {
            for (int i=0; i<9; i++)
            {
                for (int j=0; j<9; j++)
                {
                    if (input_file >> value_just_read_from_file)
                    {
                        puzzle[i][j] = value_just_read_from_file;
                    }
                }
            }
        }
        else
            cout << "Input file Data.txt does not exist in PWD" << endl;
    }
    
    // Public member function that prints the puzzle when called
    void print_puzzle()
    {
        if (0==count)
        std::cout << std::endl << "Board Position" << std::endl;
        if (count >= 1)
            std::cout << std::endl << "Solution" << count<< ":"<< std::endl;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                // check if we have a legitimate integer between 1 and 9
                if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
                {
                    // printing initial value of the puzzle with some formatting
                    std::cout << puzzle[i][j] << " ";
                }
                else {
                    // printing initial value of the puzzle with some formatting
                    std::cout << "X ";
                }
            }
            std::cout << std::endl;
        }
        count++;
    }
    
    // Public member function that (recursively) implements the brute-force
    // search for possible solutions to the incomplete Sudoku puzzle
    bool Solve(int row, int col)
    {
        if (0 == Remain_Zero_Check(row, col))//this place is key to find all solutions.
        {
            print_puzzle();
            return false;
        }
        
        for (int i = row; i <9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (0 == puzzle[i][j])
                {
                    for (int k = 1; k<=9; k++)
                    {
                        puzzle[i][j] = k;
                        // recursion to find solution
                        if ((1==row_valid(i,j)) && (1 == col_valid(i,j)) && 1 == block_valid(i, j) && Solve(i, j))
                        {
                        }
                    }
                    puzzle[i][j] = 0;
                    return false;
                }
            }
        }
        return true;
    }
    
    void print_total()
    {
         std::cout << std::endl << "There are total " <<--count<<" solution(s)!"<< std::endl;
    }
};
#endif
