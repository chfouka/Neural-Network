#ifndef LINEARUNIT_H
#define LINEARUNIT_H

#include<Unit.h>
#include<Pattern.h>

using namespace std;

class LinearUnit: public Unit
{
public:

    LinearUnit(unsigned int dimension ) : Unit(dimension) {

    }

    double getOutput(){
        return  this->getNet();
    }

    double LinearPrime( double in ){
        return 1.0;
    }

    double Update_Weights(double delta, unsigned int trainDim,
                          double eta, double lambda, double alpha){
        double net = this->getNet();

        for( unsigned int i=0; i< weights.size(); i++ ){
            double deltaweight = eta *
                    ( (delta*LinearPrime(net)*inputs[i]) -  ( 2 * lambda / trainDim) * weights[i] ) +
                    alpha * old_deltaweights[i]          ;
            weights[i] += deltaweight;
            old_deltaweights[i] = deltaweight;
        }

        return delta * LinearPrime(net);

    }

    double get_weight( unsigned int i ){
        return weights[i];
    }



};

#endif // LINEARUNIT_H
