//
//  main.cpp
//  Cauchy_RV
//
//  Created by Dongliang Yi on 11/17/15.
//  Copyright © 2015 Dongliang Yi. All rights reserved.
//

#include <cstdlib>
#include <algorithm>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

double get_uniform()
{
    return (((float) random())/(pow(2.0, 31.0)-1.0));
}

double get_cauchy()
{
    return tan(M_PI*(get_uniform() - 0.5));//get cauchy RV.
}

int main(int argc, char* argv[])
{
    double  x, mean = 0;
    unsigned int no_of_trials;
    vector <double>Cauchy_RV;
    int count[100];
    sscanf (argv[1], "%d", &no_of_trials);
    ofstream outfile(argv[2]);
    Cauchy_RV.resize(no_of_trials);
    for (int i = 0; i < 100; i++)
        count[i] = 0;
    
    
    for (int i = 0; i < no_of_trials; i++) {
        Cauchy_RV[i] = get_cauchy();
        mean += Cauchy_RV[i];
        for (int j = 0; j < 100; j++)
            if ((Cauchy_RV[i] >= ((double)(j - 51) / 10)) && (Cauchy_RV[i] < ((double)(j - 50) / 10)))
                count[j]++;//build pdf
    }
    
    mean = mean / no_of_trials;
    
    for (int j = 0; j < 100; j++)
    {
        x = (double)(j - 50) / 10;
        outfile << x << ", " << (double)(count[j])/(no_of_trials) << ", " << 0.1*(double)1 / (M_PI*(1 + x*x)) << endl;
    }
    cout <<"After {"<<no_of_trials<< "} trials: ";
    cout << "Mean of Cauchy RVs is = " << mean<<endl;
}