#ifndef SIGMOIDALUNIT_H
#define SIGMOIDALUNIT_H

#include<math.h>
#include<Unit.h>
#include<Pattern.h>
#include<vector>

class SigmoidalUnit: public Unit
{
    double Sigmoide(double in ){
        return  1.0 / ( 1.0 + exp( - 1.0 * in ) ) ;
    }

    double SigmoidePrim( double in ){
        return exp( -in ) * Sigmoide( in ) * Sigmoide( in );
    }

public:

    SigmoidalUnit( int dim ) : Unit( dim ){

    }

    double getOutput( ){
       return Sigmoide( this->getNet( ) );
    }

    double Update_Weights( double delta, unsigned int trainDim,
                           double eta, double lambda, double alpha){
        //double net = this->getNet( );
        double o = this->getOutput();

        for( unsigned int i = 0; i < weights.size( ); i++ ){           
            double deltaweight = eta *
                    ( (delta * ( 1.0 - o ) * o * inputs[i])  - ( 2 * lambda / trainDim ) * weights[i] ) +
                    alpha * old_deltaweights[i];


            weights[i] += deltaweight;
            old_deltaweights[i] = deltaweight;

        }
        //return delta * SigmoidePrim(net);
        o = this->getOutput();
        return delta * ( 1.0 - o) * o;
    }

    double get_weight(unsigned int i){
        return weights[i];
    }

};

#endif // SIGMOIDALUNIT_H
