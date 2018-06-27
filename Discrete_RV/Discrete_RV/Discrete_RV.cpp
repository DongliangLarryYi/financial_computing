//  main.cpp
//  Discrete_RV
//  Created by Dongliang Yi on 11/17/15.
//  Copyright © 2015 Dongliang Yi. All rights reserved.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

double get_uniform()
{
    return (((float) random())/(pow(2.0, 31.0)-1.0));
}

int main (int argc, char* argv[])
{
    int value_just_read_from_file;
    double value_just_read_from_file_float;
    int number_of_discrete_RV;
    double *Probability_RV;
    int no_of_trials;
    double *CDF_RV;
    int *count_number;
    ifstream input_file(argv[1]);
    sscanf (argv[2], "%d", &no_of_trials);
    //cout<<no_of_trials<<endl;
    if (input_file.is_open())
    {
        if(input_file >> value_just_read_from_file)
            number_of_discrete_RV = value_just_read_from_file;
        
        cout <<"Discrete Random Variable Generator:"<<endl;
        cout << "Events= "<< number_of_discrete_RV<<endl;
        
        Probability_RV = new double[number_of_discrete_RV];
        for(int i = 0; i < number_of_discrete_RV; i++)
        {
            if (input_file >> value_just_read_from_file_float)
            {
                Probability_RV[i]=value_just_read_from_file_float;
            }
        }
        for(int i =0; i < number_of_discrete_RV; i++)
        { 
            for(int j=i+1; j < number_of_discrete_RV; j++)
            {
                if(Probability_RV[i]<Probability_RV[j])
                {
                    float temp1= Probability_RV[i];
                    Probability_RV[i] = Probability_RV[j];
                    Probability_RV[j] = temp1;
                }
            }
        }
        
        cout << "Probability of Events:"<<endl;
        for (int i=0; i<number_of_discrete_RV; i++) 
        {
            cout<<"("<<i+1<<"): "<<Probability_RV[i]<<endl;
        }
        
        CDF_RV =new double[number_of_discrete_RV];
        CDF_RV[0]=0;
        for(int i = 1; i <= number_of_discrete_RV; i++)
        {
            CDF_RV[i]=CDF_RV[i-1]+Probability_RV[i-1];
            //cout<< CDF_RV[i]<<endl;
        }
        
        count_number=new int[number_of_discrete_RV];
        for (int i = 0; i < no_of_trials; i++)
        {
            double x = get_uniform();
            for (int j = 1; j <= number_of_discrete_RV; j++)
            {
                if (x<CDF_RV[j])
                    count_number[j]++;
            }
        }// sum the CDF
        cout << "Empirical Results after {"<<no_of_trials<<"} trials:"<<endl;
        cout<<"(1): "<<(double)count_number[1]/no_of_trials<<endl;
        for (int i = 2; i <= number_of_discrete_RV; i++)
        {
            cout<<"("<<i<<"): "<<(double)count_number[i]/no_of_trials-((double)count_number[i-1]/no_of_trials)<<endl;
        }
    }
    else
        cout<<"Input error, please check!";
}
