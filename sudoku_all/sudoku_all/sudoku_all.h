//
//  sudoku_all.h
//  sudoku_all
//
//  Created by Dongliang Yi on 9/14/15.
//  Copyright (c) 2015 Dongliang Yi. All rights reserved.
//

#ifndef sudoku_all
#define sudoku_all

#include <vector>
#include <fstream>
using std::vector;
using namespace std;
class Sudoku
{
    // Private
    int puzzle[9][9];
    
    int count = 0;//this is used to count all solutions
    
    bool Remain_Zero_Check(int row, int col) // this is used to check whether there is any zero left.
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
    
    
    // Private member function that checks if the named row is valid
    bool row_valid(int row, int col)//check row
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
        // write code that checks if "row" is valid
    }
    
    // Private member function that checks if the named column is valid
    bool col_valid(int row, int col)//check col
    {
        
        for (int x = 0; x <9; x++ ) {
            
            if (x == row) {
                //x++;
            }
            
            else
                if (puzzle[row][col] == puzzle[x][col]) {
                    return false;
                }
            
        }
        return true;
        // check validity of "col"
    }
    
    // Private member function that checks if the named 3x3 block is valid
    bool block_valid(int row, int col)//check block, details please see previous one
    {
        if (0 == row && 0 == col)
        { for (int i = 0; i < 3; i++)
        {
            
            
            for (int j = 0; j < 3; j++)
            {
                
                if ( i == row && j == col) {
                    //j++;
                }
                
                
                else
                    if(puzzle[row][col] == puzzle[i][j])
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
                    
                    if ( i == row && j == col) {
                        //j++;
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
                    if ( i == row && j == col) {
                        // j++;
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
                    if ( i == row && j == col) {
                        // j++;
                    }
                    
                    
                    else
                        if(puzzle[row][col] == puzzle[i][j])
                            return false;
                    
                }
            }
            
        }
        
        return true;
        // check 3 x 3 block validity
    }
    
public:
    // Public member function that reads the incomplete puzzle
    // we are not doing any checks on the input puzzle -- that is,
    // we are assuming they are indeed valid
    void read_puzzle(int argc, char * const argv[])
    {
        
        ifstream input_file(argv[1]);
        
        int value_just_read_from_file;
        
        if (input_file.is_open()) // If "Data.txt" exists in the local directory
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
        
        // write code that reads the input puzzle using the
        // guidelines of figure 23 of the bootcamp material
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
        /*if ( row > 8 && col > 8)
        {
            
            //print_puzzle();
            
            return true;
         
        }*/
        
        if (0 == Remain_Zero_Check(row, col))//this place is key to find all solutions.
        {
            print_puzzle();
            return false;
        }
        
        /*for (int i = 0; i <9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
              if ( 0 == puzzle[i][j])
                  ;
              else
                  print_puzzle();
                  return false;
            }
        }*/
        
        
        for (int i = row; i <9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (0 == puzzle[i][j])
                {
                    for (int k = 1; k<=9; k++)
                    {
                        puzzle[i][j] = k;
                        if ((1==row_valid(i,j)) && (1 == col_valid(i,j)) && 1 == block_valid(i, j) && Solve(i, j))
                        {
                            
                            //print_puzzle();
                            //return true;
                            
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

    
    
    // this part of the code identifies the row and col number of the
    // first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
    // no zeros, the variable row will be 9 => the puzzle is done, as
    // each entry is row-, col- and block-valid...
    
    // use the pseudo code of figure 3 of the description
    
};

#endif
