//  Price American Options with Trinomial Trees and Memoization. It cost less time with memoization.
//  Created by Dongliang Yi on 11/23/15.
//  Copyright © 2015 Dongliang Yi. All rights reserved.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

// Use class for calculating the price with ease
class Option_Calculation
{
    vector <vector <double> > Call_Option; // this matrix is used for memoization for call;
    vector <vector <double> > Put_Option; // this matrix is used for memoization for put;
    // declared six variables: factor, probability of price up, probability of price down, probability of price unchanged, risk free rate, option strike price
    double up_factor, uptick_prob, downtick_prob, notick_prob, risk_free_rate, strike_price;
    // declared four variables: initial stock price, expiration date, constant volatility and R factor
    double initial_stock_price, expiration_time, volatility, R;
    int no_of_divisions;

// function to return bigger number    
double max(double a, double b) 
{
    return (b < a )? a:b;
}

double american_call_option(int k, int i, double current_stock_price)
{
    // check whether there have been the value stored in the Call_Option matrix
    if (Call_Option[k][i+no_of_divisions]> -0.1) // number bigger than -0.1 means there have been value change after initializing all number to -1
    {
        return Call_Option[k][i+no_of_divisions]; //shift "no_of_divisions" to store value
    }
    
    // only execute below code when the value was not calculated previously
    if (k == no_of_divisions)
    {
        // if this is the final stage
        //store intermediate value, used for memoization
        Call_Option[k][i+no_of_divisions]=max(0.0, (current_stock_price - strike_price));
        return Call_Option[k][i+no_of_divisions];
    }
    else
    {
        // if not the final stage, calculate the expected value. Will do recursion
        //store intermediate value, used for memoization
        Call_Option[k][i+no_of_divisions]=max((current_stock_price - strike_price),(uptick_prob*american_call_option(k+1, i+1, current_stock_price*up_factor)+(notick_prob)*american_call_option(k+1, i, current_stock_price)+(downtick_prob)*american_call_option(k+1, i-1, current_stock_price/up_factor))/R);
        return Call_Option[k][i+no_of_divisions];
    }
}

double american_put_option(int k, int i, double current_stock_price)
{
    // check whether there have been the value stored in the Put_Option matrix
    if (Put_Option[k][i+no_of_divisions]> -0.1) 
    {
        return Put_Option[k][i+no_of_divisions];
    }
    
    // only execute below code when the value was not calculated previously
    if (k == no_of_divisions)
    {
        // if this is the final stage
        //store intermediate value, used for memoization
        Put_Option[k][i+no_of_divisions]=max(0.0, (strike_price - current_stock_price));
        return Put_Option[k][i+no_of_divisions];
    }
    else
    {
        // if not the final stage, calculate the expected value. Will do recursion
        //store intermediate value, used for memoization
        Put_Option[k][i+no_of_divisions]=max((strike_price - current_stock_price),(uptick_prob*american_put_option(k+1, i+1, current_stock_price*up_factor) +notick_prob*american_put_option(k+1, i, current_stock_price)+ (downtick_prob)*american_put_option(k+1, i-1, current_stock_price/up_factor))/R);
        return Put_Option[k][i+no_of_divisions];
    }
}
 
public:
    void initialize(int argc, char* argv[])
    {
        // input from command line
        sscanf (argv[1], "%lf", &expiration_time);
        sscanf (argv[2], "%d", &no_of_divisions);
        sscanf (argv[3], "%lf", &risk_free_rate);
        sscanf (argv[4], "%lf", &volatility);
        sscanf (argv[5], "%lf", &initial_stock_price);
        sscanf (argv[6], "%lf", &strike_price);
        
        // calculate variables used in trinomial trees
        R = exp(risk_free_rate*expiration_time/((float) no_of_divisions));
        up_factor = exp(volatility*sqrt((2*expiration_time)/((float) no_of_divisions)));
        uptick_prob = pow((sqrt(R) - 1/sqrt(up_factor))/(sqrt(up_factor)-1/sqrt(up_factor)),2);
        downtick_prob = pow((sqrt(up_factor) - sqrt(R))/(sqrt(up_factor)-1/sqrt(up_factor)),2);
        notick_prob = 1 - uptick_prob - downtick_prob;
        
        // initializing the matrices used for memoization
        vector <double> temp(2*no_of_divisions+1,-1);
        for (int i = 0; i <= no_of_divisions; i++)
        {
            Put_Option.push_back(temp);
            Call_Option.push_back(temp);
        }
    }
    
    void print()
    {
        // output values
        cout << "Recursive Trinomial American Option Pricing" << endl;
        cout << "Expiration Time (Years) = " << expiration_time << endl;
        cout << "Number of Divisions = " << no_of_divisions << endl;
        cout << "Risk Free Interest Rate = " << risk_free_rate << endl;
        cout << "Volatility (%age of stock value) = " << volatility*100 << endl;
        cout << "Initial Stock Price = " << initial_stock_price << endl;
        cout << "Strike Price = " << strike_price << endl;
        cout << "--------------------------------------" << endl;
        cout << "R = " << R << endl;
        cout << "Up Factor = " << up_factor << endl;
        cout << "Uptick Probability = " << uptick_prob << endl;
        cout << "Downtick Probability = " << downtick_prob << endl;
        cout << "Notick Probability = " << notick_prob << endl;
        cout << "--------------------------------------" << endl;
        cout << "Trinomial Price of an American Call Option = " << american_call_option(0, 0,initial_stock_price) << endl;
        cout << "Trinomial Price of an American Put Option = " << american_put_option(0, 0, initial_stock_price) << endl;
    }
};

int main (int argc, char* argv[])
{
    // call and run functions    
    Option_Calculation Option_Cal;
    Option_Cal.initialize(argc, argv);
    Option_Cal.print();
}
