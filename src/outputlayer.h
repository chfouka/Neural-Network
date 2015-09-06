#ifndef OUTPUTLAYER_H
#define OUTPUTLAYER_H

#include<vector>
//#include<sigmoidalunit.h>
#include<linearunit.h>
#include<Pattern.h>

using namespace std;

class OutputLayer
{
   unsigned int hiddendimension;
   // vector<SigmoidalUnit> units;
   vector<LinearUnit> units;
   vector<double> inputs;

public:
    OutputLayer();

    OutputLayer(int dim, int hid){
        hiddendimension = hid;
        for(int i =0 ; i < dim ; i++ ){
            units.push_back(LinearUnit(hiddendimension));
        }
    }

    void setInputs( vector<double>& in ){
        if(in.size() != hiddendimension )
            cerr << "OutputLayer: input wrong dimension" << endl;
        else{
            inputs = in;
            for(unsigned int i = 0; i < units.size(); i++ )
                units[i].setInputs(in);
        }
    }

    vector<double> getOutputs( ){
        vector<double> outs;
        for( unsigned int i = 0 ; i < units.size(); i++ ){
            outs.push_back( units[i].getOutput( ) );
        }
        return outs;

    }

    LinearUnit getUnit( int index ){
        return units[index];
    }


/*
    SigmoidalUnit getUnit( int index ){
        return units[index];
    }
*/
    void Initialize( ){
        for( unsigned int i = 0; i < units.size(); i++ ){
            units[i].Initialize();
        }
    }

    vector<double> Update_Weights( vector<double>& targets, unsigned int trainDim,
                                   double eta, double lambda, double alpha ){
        vector<double> deltas;
       if( targets.size() != units.size() )
            cerr << "OutLayer: wrong target size" << endl;

       else{
            for(unsigned int i = 0; i < units.size() ; i++ ){
                double delta = targets[i] - units[i].getOutput();
                double d = units[i].Update_Weights(delta, trainDim, eta, lambda, alpha);
                deltas.push_back(d);
            }
        }
       return deltas;
    }


    void print (){
        for(unsigned int i = 0; i<units.size(); i++ ){
            cout << "**** unit O" << i << " ****";
            units.at(i).print_weights();
            cout << endl;
        }

    }

};

#endif // OUTPUTLAYER_H
