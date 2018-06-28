// We have two players Alice and Bob,
// each have a coin that they can toss. The probability of heads for Alice’s coin
// is q, and that for Bob’s coin is p, where q < p. They agree to to the following
// game
// Each will toss their respective coins n times, Alice wins if and only
// if she gets more heads than Bob at the end of the n-many tosses.
// Obviously, the game favors Bob over Alice, but reference [1] studies the following
// problem
// What is the optimal value of n that will maximize Alice’s chance of
// winning?

// [1] V. Addona, S. Wagon, and H. Wilf. How to lose as little as possible. ARS
// MATHEMATICA CONTEMPORANEA, 4:29–62, 2011.

//  Created by Dongliang Yi on 11/9/15.
//  Copyright © 2015 Dongliang Yi. All rights reserved.

#ifndef Least_Loss_h
#define Least_Loss_h
#include <cmath>
using namespace std;

class I_have_nothing_apropos_for_this_class
{
private:
    double alice_probability, bob_probability;
    // private member function: uniform RV generator
    double get_uniform()
    {
        return (((float) random())/(pow(2.0, 31.0)-1.0));
    }
    
    int take(int n, int i)
    {
        if (i == 0)
            return(1);
        else
            return (take(n, i - 1)*(n-i+1) / i); //recursion to calculation combination
    }
    
    double theoretical_value(double q, double p, int n)
    {
        // implement equation 1.1 of Addona-Wagon-Wilf paper
        double possibility_of_s_greater_than_r=0, possibility_of_Alice_win=0;
        int r,s;
        for (r = 0; r <= n; r++)
        {
            possibility_of_s_greater_than_r = 0;
            for (s = r + 1; s <= n; s++)
            {
                possibility_of_s_greater_than_r += (double)take(n, s)*pow(q, s)*pow(1 - q, n - s);
            }
            possibility_of_s_greater_than_r *= (double)take(n, r)*pow(p, r)*pow(1 - p, n - r);
            possibility_of_Alice_win += possibility_of_s_greater_than_r;
        }
        
        return possibility_of_Alice_win;
        // this is to calculated the expectation of winning for Alice.
    }
    
public:
    // public function:
    void set_probability(double alice_p, double bob_p)
    {
        alice_probability = alice_p;
        bob_probability = bob_p;
    }
    
    // probability of Alice winning the game.
    double simulated_value(int number_of_coin_tosses_in_each_game, int no_of_trials)
    {
        int no_of_wins_for_alice = 0;
        for (int i = 0; i < no_of_trials; i++)
        {
            int number_of_heads_for_alice = 0;
            int number_of_heads_for_bob = 0;
            for (int j = 0; j < number_of_coin_tosses_in_each_game; j++)
            {
                double temp = get_uniform();
                double temp2 = get_uniform();
                if (temp < alice_probability)
                    number_of_heads_for_alice++;
                if (temp2 < bob_probability)
                    number_of_heads_for_bob++;
            }
            if (number_of_heads_for_alice > number_of_heads_for_bob)
                no_of_wins_for_alice++;
        }
        return (((double) no_of_wins_for_alice)/no_of_trials);
    }
    
    int search_result(double alice,double bob)
    {
        // colde according to the theorem 2.2 to find the optimal number.
        float fn = 0, fn_minus_one = 0, fn_plus_one = 0;
        int n = 1;
        do
        {
            n++;
            fn_minus_one = theoretical_value(alice_probability, bob_probability, n - 1);
            fn = theoretical_value(alice_probability, bob_probability, n);
            fn_plus_one = theoretical_value(alice_probability, bob_probability, n + 1);
        } while (fn < fn_minus_one || fn < fn_plus_one);
        
        cout << "The theoretical optimal winning possibility for Alice is " << theoretical_value(alice, bob, n) <<" for " << n << " tosses!"<<endl;
        return n;
    }
};
#endif
