#ifndef PATTERN_H
#define PATTERN_H

#include<vector>

using namespace std;

class Pattern
{
public:
    vector<double> inputs;
    vector<double> outputs;

public:

    Pattern(vector<double>& in , vector<double>& out) {
        inputs = in;
        outputs = out;
    }

   void Addin(double d){
        inputs.push_back(d);
   }

   void Addout(double d){
        outputs.push_back(d);
   }

   friend ostream& operator << (ostream& out, Pattern& p){
       for( unsigned int i = 0 ; i < p.inputs.size(); i++ )
           out << p.inputs[i] << " ";
       for( unsigned i = 0 ; i < p.outputs.size(); i++ )
           out << p.outputs[i] << " ";

        //out << endl;
        return out;
   }
};

#endif // PATTERN_H
