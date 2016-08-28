//
//  N_Queens_Problem
//
//  Created by Dongliang Yi on 9/10/15.
//  Copyright (c) 2015 Dongliang Yi. All rights reserved.
//

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
        //return true; //test use
        
        for (int i = 0 ; i < col; i++) //this is used to make sure it is safe on the same row
        {
            if (1 == chess_board[row][i])
            {
                return false;
            }
        }
        
        
        for (int i = 0 ; i < row; i++)//this is used to check the safety on the same colume
        {
            if (1 == chess_board[i][col])
            {
                return false;
            }
        }
        
        
        for (int i = 0 ; (row-i) >= 0 && (col-i) >= 0 ; i++) { //check diagonal
            if (1 == chess_board[row-i][col-i]) {
                return false;
            }
        }
        
        for (int i = 0 ; (row+i) < size && (col-i) >= 0 ; i++) {//check back-diagonal
            if (1 == chess_board[row+i][col-i]) {
                return false;
            }
        }
        
        return true;
    }

/*
        
        if ( 0 == col )
            return true;
        if ( 0 == row )
        {
            if ( 1 == chess_board[row][col-1] || 1 == chess_board[row+1][col-1])
                return false;
        return true;
        }
        if ( size - 1 == row )
        {
            if ( 1 == chess_board[row][col-1] || 1 == chess_board[row-1][col-1])
                return false;
        return true;
        }
        if ( 0 < row && row < size - 1 )
        {
            if (1 == chess_board[row][col-1] || 1 == chess_board[row-1][col-1] || 1== chess_board[row+1][col-1])
                return false;
        return true;
        }
        return false;
    */
    
        
        // write the appropriate code on your own that returns
        // "true" if the (row,col) position is safe.  If it is
        // unsafe (i.e. some other queen can threaten this position)
        // return "false"
        
    
    
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

        
        // write the appropriate code that uses the pointer-to-pointer
        // method to initialize the (n x n) chessboard.  Once initialized,
        // put zeros in all entries.  Later on, if you placed a queen in
        // the (i,j)-th position, then chessboard[i][j] will be 1.
    }
    
    // private member function: prints the board position
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

        // write the appropriate code here to print out the solved
        // board as shown in the assignment description
        
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
        
        // implement the recursive backtracking procedure described in
        // pseudocode format in figure 1 of the description of the first
        // programming assignment
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