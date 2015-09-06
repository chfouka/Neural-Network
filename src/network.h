#ifndef NETWORK_H
#define NETWORK_H

#include<hiddenlayer.h>
#include<outputlayer.h>
#include<Dataset.h>
#include<math.h>
#include<vector>

using namespace std;

class Network
{
    OutputLayer outLayer;
    HiddenLayer hidLayer;
    unsigned int inputDimension;
    unsigned int outputDimension;
    unsigned int hidDimension;

public:
    Network( unsigned int indim, unsigned int outdim, unsigned int hidim ) : outLayer(outdim, hidim+1),
        hidLayer( hidim, indim+1)
    {
      inputDimension = indim;
      outputDimension = outdim;
      hidDimension = hidim;
    }

    vector<double> getOutput( ){
       return outLayer.getOutputs();
    }


    double learnBackPro( Dataset& training, Dataset& validation, unsigned int times,
                       double etas, double etal, double lambda, double alpha, bool earlystop, Dataset test = Dataset()  ){
        /**
         * Si usa l'early stopping come criterio di arresto (oltre un maxnum di epoche)
         * Ad ogni 15 epoche viene valutato l'errore MSE sul validation set, se questo non
         * decresce rispetto all'ultima valutazione allora si stoppa il training in quanto
         * questo potrebbe essere un sintomo di overfitting.
         **/

        unsigned int epoca = 0;
        double validation_error = 0.0;
        double training_error = 0.0;
        double test_error = 0.0;
        double avg_verror = 0;
        double minavg_verror = std::numeric_limits<double>::max();;
        unsigned int minEpoch = 0;
        double minvalidation = std::numeric_limits<double>::max();

        /*Initialization*/
        srand (time(NULL));
        hidLayer.Initialize();
        outLayer.Initialize();

        /*Iteration*/
        while ( epoca < times ){
            for( unsigned int i = 0; i < training.data.size(); i ++ ){
                vector<double> input = training.data[i].inputs;
                input.push_back(1.0);
                hidLayer.setInputs(input);
                vector<double> outHidden = hidLayer.getOutputs();
                outHidden.push_back(1.0);
                outLayer.setInputs(outHidden);

                vector<double> outLayer_deltas =
                        outLayer.Update_Weights(training.data[i].outputs, training.data.size(), etal, lambda, alpha);

                /*calcoli per i deltas dell'hidden*/
                vector<double> deltas;

                for(unsigned int i = 0; i < hidDimension; i++){
                    double delta = 0.0;
                    for( unsigned int j = 0; j < outputDimension; j++ ){
                        double d = outLayer.getUnit(j).get_weight(i);
                        delta += outLayer_deltas[j] * d;
                    }
                    deltas.push_back(delta);
                }

                hidLayer.Update_Weights(deltas, training.data.size(), etas, lambda, alpha);
                deltas.clear();
            }


            //durante il learning la valutazione dell'errore è sempre su dati normalizzati
            training_error = error_MSE(training, 0);
            validation_error = error_MSE(validation, 0);
            if(test.data.size() != 0)
                test_error = error_MSE(test, 0);

            if (validation_error < minvalidation) minvalidation = validation_error;

            if(earlystop){
            avg_verror += validation_error / 20 ;

            if( epoca != 0 && ( epoca % 20 ) == 0 ){
                if(avg_verror < minavg_verror){
                    minavg_verror = avg_verror;
                    minEpoch = epoca;
                }
                else{
                    if( epoca - minEpoch > 400 ){
                      cerr << "EARLY STOP " << minEpoch << endl;
                      break;
                    }
                }

                avg_verror = 0;
            }
}
            cout << epoca << " "
             << training_error << " "
             << validation_error << " ";
             if(test.data.size()!= 0)
                cout << test_error;
             cout << endl;

        /*
            // per il monk posso anche calcolare l'accuracy
            double training_accuracy = ClassifyTst(training, 0.5 );
            double validation_accuracy = ClassifyTst(validation, 0.5);
            double test_accuracy;
            if(test.data.size() != 0)
                test_accuracy = ClassifyTst(test, 0.5);


            cout << epoca << " "
                 << training_accuracy << " ";
                 if(validation.data.size()!= 0)
                    cout << validation_accuracy << " ";
                if(test.data.size()!= 0)
                    cout << test_accuracy;
                cout << endl;
    */
            epoca += 1;
            }

        //return validation_error;
        return minvalidation;
    }

    vector<double> Classify(vector<double> inputs){
        /*Calcola l'uscita della rete su un dato input*/
        inputs.push_back(1.0);
        hidLayer.setInputs(inputs);
        vector<double> outHidden = hidLayer.getOutputs();
        outHidden.push_back(1.0);
        outLayer.setInputs(outHidden);
        vector<double> outs = outLayer.getOutputs();
        return outs;
    }


    double ClassifyTst( Dataset test, double treshold ){
        /*calcola l'accuracy di classificazione su un dataset*/
        unsigned int missed = 0;
        for(unsigned int i = 0; i < test.data.size(); ++i ){
            Pattern pattern = test.data[i];
            vector<double> outs = Classify(pattern.inputs);
            bool wrong = false;
            for( unsigned int j = 0; j < outs.size(); ++j ){
                if( fabs( outs[j] - pattern.outputs[j] ) > treshold )
                    wrong = true;
            }
            if(wrong) missed ++;
        }

        //cerr << "missed " << missed << " total " << test.data.size( ) << endl;
        return (double ( test.data.size() - missed ) / double( test.data.size( ) )) * 100 ;
    }


    void Print_Weights( ){
        /*Stampa i pesi della rete, utile per il debugging*/
        cerr << "******     HiddenLayer     *******" << endl;
        hidLayer.print( );
        cerr << "******    OutputLayer     ********" << endl;
        outLayer.print( );
    }

    double error_MSE(Dataset test, bool descale){
       /** computes the Mean Squared Error
        * MSE = 1/N ( Sum_p ||o_p - t_p|| ^ 2 )
        **/
        double sum = 0.0;

        for(unsigned int i = 0; i<test.data.size(); i++){
            Pattern pattern = test.data.at(i);
            vector<double> outs = Classify(pattern.inputs);
            if( outs.size() != pattern.outputs.size() )
                cerr << "error_MSE: wrong dimensions" << endl;
            Pattern pattern_classified(pattern.inputs, outs);

            /*eventualmente conto l'errore su dati riscalati*/

            if(descale){
                test.descale(pattern);
                test.descale(pattern_classified);
            }

            outs = pattern_classified.outputs;
            vector<double> targets = pattern.outputs;
            // vettore differenza e norma
            vector<double> diff;
            diff.assign(pattern.outputs.size(), 0);
            double norma_2 = 0.0;
            for(unsigned int j=0; j< outs.size(); j++)
                diff.at(j) = targets[j] - outs[j];
            for(unsigned int j = 0; j<diff.size(); j++)
                norma_2 += diff.at(j) * diff.at(j);

            sum = sum + norma_2;


        }
        return sum /  ( test.data.size() );
    }


    double error_MEE(Dataset test, bool descale){
        /***computes the Mean Euclidean Error
            MEE = 1/N ( Sum_p ||o_p - t_p||  )
        ***/

        double sum = 0.0;

        for(unsigned int i = 0; i<test.data.size(); i++){
            Pattern pattern = test.data.at(i);
            vector<double> outs = Classify(pattern.inputs);
            if( outs.size() != pattern.outputs.size() )
                cerr << "error_MSE: wrong dimensions" << endl;
            Pattern pattern_classified(pattern.inputs, outs);

            if(descale){
                test.descale(pattern);
                test.descale(pattern_classified);
            }

            outs = pattern_classified.outputs;
            vector<double> targets = pattern.outputs;
            // vettore differenza e norma
            vector<double> diff;
            diff.assign(pattern.outputs.size(), 0);
            double norma_2 = 0.0;
            for(unsigned int j=0; j< outs.size(); j++)
                diff.at(j) = targets[j] - outs[j];
            for(unsigned int j = 0; j<diff.size(); j++)
                norma_2 += diff.at(j) * diff.at(j);

            sum += sqrt (norma_2);
        }
        return sum /  ( test.data.size() ) ;
    }

};

#endif // NETWORK_H

