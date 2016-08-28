//
//
//  Created by Dongliang Yi on 11/9/15.
//  Copyright © 2015 Dongliang Yi. All rights reserved.
//

// IE523: Financial Computation
// "How to lose as little as possible" by Addona, Wagon and Wilf
// Written by Prof. Sreenivas
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "Least_Loss.h"
using namespace std;

int main (int argc, char* argv[])
{
    I_have_nothing_apropos_for_this_class x;
    double alice_success_prob, bob_success_prob;
    sscanf (argv[1], "%lf", &alice_success_prob);
    sscanf (argv[2], "%lf", &bob_success_prob);
    
    cout << endl<< "Probability of success for Alice = " << alice_success_prob << endl;
    cout << "Probability of success for Bob = " << bob_success_prob << endl;
    
    x.set_probability(alice_success_prob, bob_success_prob);
    
    int optimal = x.search_result(alice_success_prob,bob_success_prob);
    
    cout<<"----------------------------------------------------"<<endl;
    cout << "Below is simulation:"<<endl;
    
    cout << "When Toss "<< optimal<< " times, the possibility of wining for Alice is: "<< x.simulated_value(optimal, 1000000)<<endl<<endl;//toss 1000000 times.

    
        
        
        

}