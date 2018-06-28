// The original version of this problem goes like this – You have a 8 × 8 chessboard, and you have to place 8 queens on this chessboard such that no two of
// them threaten each other. Since a queen can attack any piece that shares a row,
// column, or diagonal, with it, we are essentially looking to place 8 elements in a
// 8 × 8 grid such that no two of them share a common row, column, or diagonal.
// The n × n version of this problem asks you to place n queens on a n × n
// chessboard.
//  Created by Dongliang Yi on 9/10/15.
//  Copyright (c) 2015 Dongliang Yi. All rights reserved.

#ifndef N_queens
#define N_queens
using namespace std;
class Board
{
    // private data member: size of the board
    int size;
    // pointer-to-pointer initialization of the board
    int **chess_board;
    // private member function:  returns 'false' if
    // the (row, col) position is not safe.
    bool is_this_position_safe(int row, int col)
    {
        //this is used to make sure it is safe on the same row
        for (int i = 0 ; i < col; i++) 
        {
            if (1 == chess_board[row][i])
            {
                return false;
            }
        }
        //this is used to check the safety on the same colume
        for (int i = 0 ; i < row; i++)
        {
            if (1 == chess_board[i][col])
            {
                return false;
            }
        }
        //check diagonal
        for (int i = 0 ; (row-i) >= 0 && (col-i) >= 0 ; i++) 
        { 
            if (1 == chess_board[row-i][col-i]) 
            {
                return false;
            }
        }
        //check back-diagonal
        for (int i = 0 ; (row+i) < size && (col-i) >= 0 ; i++) 
        {
            if (1 == chess_board[row+i][col-i]) 
            {
                return false;
            }
        }
        return true;
    }
    
    // private member function: initializes the (n x n) chessboard
    void initialize(int n)
    {
        size = n;
        chess_board = new int*[size];
        for (int i = 0; i < size; i++) // initialize array
            chess_board[i] = new int[size];
        
        for (int i = 0; i < size; i++) // define array
        {
            for (int j = 0; j < size; j++)
            {
                chess_board[i][j] = 0;
            }
        }
    }
    // private member function: prints the solved board position
    void print_board()
    {
        std::cout << size << "-Queens Problem Solution" << std::endl;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if ( 1 == chess_board[i][j])
                    cout << "Q" << " "; // this is chess
                else
                    cout << "-" << " "; // this is not chess
            }
            cout << endl;
        }
    }
    
    // private member function: recursive backtracking
    bool solve(int col)
    {
        if (col >= size)
           return true;
        else
        {
            for (int row = 0; row < size; row++) // find solution
            {
                if (is_this_position_safe(row, col))
                {
                    chess_board[row][col] = 1; // mark the chess
                    if (solve(col + 1)) // recursion
                    {
                        return true;
                    }
                    else
                        chess_board[row][col] = 0;
                }
            }
            return false;
        }
    }
    
public:
    // Solves the n-Queens problem by (recursive) backtracking
    void nQueens(int n)
    {
       initialize(n);        
       if (solve(0))
            print_board();
       else
            std::cout << "There is no solution to the " << n << "-Queens Problem" << std::endl;
    }
};
#endif
