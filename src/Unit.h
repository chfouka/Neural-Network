#ifndef UNIT_H
#define UNIT_H

#include<iostream>
#include<vector>
#include<cstdlib>
#include <stdlib.h>
#include <time.h>


using namespace std;

class Unit
{
protected:
    vector<double> weights;
    vector<double> old_deltaweights;
    vector<double> inputs;
    int id;

public:
    Unit( int dim ){
        for( int i = 0 ; i< dim ; i++){
            weights.push_back( 0.0 );
            old_deltaweights.push_back(0.0);
        }
    }

    void setInputs( vector<double>& in ){
        if(in.size() != weights.size())
            cerr << "Unit: error: wrong input size" ;
        else
            inputs = in;
    }


    void Initialize( ){
        for (unsigned int i = 0; i < weights.size(); i++){
            double f = (double) rand() / RAND_MAX;
           // weights[i] =  -0.5 + f * (0.5 + 0.5);
            weights[i] =  -1 + f * (1 + 1);
        }
    }

    double getNet(){
        double net = 0.0;

        for(unsigned int i = 0; i < inputs.size(); i++ )
            net += weights[i] * inputs[i];

        return net;
    }

    double getOutput();

    double get_weight(unsigned int i);

    void print_weights(){
        cout << "[ ";
        for( unsigned int i = 0; i< weights.size(); i++)
            cout << weights[i] << " ";
        cout << "]"<< endl;
    }

};

#endif // UNIT_H
