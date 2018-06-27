//  This code prices American Option with Trinomial Trees and Lattices
//  Created by Dongliang Yi on 11/23/15.
//  Copyright © 2015 Dongliang Yi. All rights reserved.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;

// declared six variables: factor, probability of price up, probability of price down, probability of price unchanged, risk free rate, option strike price 
double up_factor, uptick_prob, downtick_prob, notick_prob, risk_free_rate, strike_price; 
// declared four variables: initial stock price, expiration date, constant volatility and R factor
double initial_stock_price, expiration_time, volatility, R;
int no_of_divisions;

// function to return bigger number
double max(double a, double b) {
    return (b < a )? a:b;
}

// return the value of the call option.
double american_call_option(int k, int i, double current_stock_price)
{
    // if in the final stage, return the bigger number between zero and (current price - strike price)
    if (k == no_of_divisions)
        return max(0.0, (current_stock_price - strike_price));
    // if not the final stage, return the expected value of the option. Here will have recursion. 
    else
        return max((current_stock_price - strike_price),(uptick_prob*american_call_option(k+1, i+1, current_stock_price*up_factor)+(notick_prob)*american_call_option(k+1, i, current_stock_price)+(downtick_prob)*american_call_option(k+1, i-1, current_stock_price/up_factor))/R);
}

// return the value of the put option.
double american_put_option(int k, int i, double current_stock_price)
{
    // if in the final stage, return the bigger number between zero and (strike price - current price)
    if (k == no_of_divisions)
        return max(0.0, (strike_price - current_stock_price));
    // if not the final stage, return the expected value of the option. Here will have recursion. 
    else
        return max((strike_price - current_stock_price),(uptick_prob*american_put_option(k+1, i+1, current_stock_price*up_factor) +notick_prob*american_put_option(k+1, i, current_stock_price)+ (downtick_prob)*american_put_option(k+1, i-1, current_stock_price/up_factor))/R);
}

int main (int argc, char* argv[])
{
    // input of six variables from command line
    sscanf (argv[1], "%lf", &expiration_time);
    sscanf (argv[2], "%d", &no_of_divisions);
    sscanf (argv[3], "%lf", &risk_free_rate);
    sscanf (argv[4], "%lf", &volatility);
    sscanf (argv[5], "%lf", &initial_stock_price);
    sscanf (argv[6], "%lf", &strike_price);
    
    // calculate variables according to formulas
    R = exp(risk_free_rate*expiration_time/((float) no_of_divisions));
    up_factor = exp(volatility*sqrt((2*expiration_time)/((float) no_of_divisions)));
    uptick_prob = pow((sqrt(R) - 1/sqrt(up_factor))/(sqrt(up_factor)-1/sqrt(up_factor)),2);
    downtick_prob = pow((sqrt(up_factor) - sqrt(R))/(sqrt(up_factor)-1/sqrt(up_factor)),2);
    notick_prob = 1 - uptick_prob - downtick_prob;
    
    // output of the values
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

