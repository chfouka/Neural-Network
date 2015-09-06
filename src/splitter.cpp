#include<iostream>
#include<Dataset.h>
#include <boost/program_options.hpp>

using namespace boost::program_options;

using namespace std;

int main(int argc, char** argv)
{
    int numInput;
    int numOutput;
    string dataset;
    string testPath;
    string trainPath;
    string normvaluesPath;
    double p;


    // Declare the supported program options
    options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce this help message")
            ("numInput,i",value<int>(&numInput), "number of inputs")
            ("numOutput,o",value<int>(&numOutput), "number of outputs")
            ("datasetPath,d",value<string>(&dataset), "dataset path")
            ("trainingsetPath,t",value<string>(&trainPath), "training set path")
            ("testsetPath,s",value<string>(&testPath), "test set path, optioinally ")
            ("fraction,f", value<double>(&p), "fraction of dataset for training")
            ("normValuesPath,n",value<string>(&normvaluesPath), "max min values file path")
            ;

    variables_map vm;

    try {
        store(parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            cout << desc << "\n";
            exit( 1 );
        }

        notify(vm);
    } catch ( error& e ) {
        cerr << desc << endl;
        cerr << e.what() << endl;
        exit( 1 );
    }

    if (!vm.count("numInput")) {
        cerr << desc << endl;
        cerr << "option --number of inputs is required.\n";
        exit( 1 );
    }

    if (!vm.count("numOutput")) {
        cerr << desc << endl;
        cerr << "option --number of outputs is required.\n";
        exit( 1 );
    }

    if (!vm.count("datasetPath")) {
        cerr << desc << endl;
        cerr << "option --dataset path is required.\n";
        exit( 1 );
    }

    if (!vm.count("trainingsetPath")) {
        cerr << desc << endl;
        cerr << "option --trainingset path is required.\n";
        exit( 1 );
    }

    if (!vm.count("testsetPath")) {
        cerr << desc << endl;
        cerr << "option --testset path is required.\n";
        exit( 1 );
    }

    if (!vm.count("normValuesPath")) {
        cerr << desc << endl;
        cerr << "option --max min values file path is required.\n";
        exit( 1 );
    }

    if (!vm.count("fraction")) {
        cerr << desc << endl;
        cerr << "option --fraction of data for training is required.\n";
        exit( 1 );
    }


    Dataset ds(dataset.c_str(),numInput, numOutput);
    ds.shuffle();

    vector<Pattern> train_patt;
    vector<Pattern> test_patt;
    Dataset training(train_patt, numInput, numOutput,ds.maxInputs, ds.minInputs, ds.maxOutputs, ds.minOutputs);
    Dataset testing(test_patt, numInput, numOutput,ds.maxInputs, ds.minInputs, ds.maxOutputs, ds.minOutputs);

    ds.split(&training, &testing, p);

    // scrivo tutto in files
    ofstream trainfile;
    trainfile.open(trainPath);

    for(unsigned int i = 0; i < training.data.size(); ++i){
        Pattern p = training.data.at(i);
        for(unsigned int j = 0; j < p.inputs.size(); ++ j)
            trainfile << p.inputs.at(j) << " ";
        for( unsigned j = 0; j < p.outputs.size(); ++j)
            trainfile << p.outputs.at(j) << " ";
        trainfile << "\n";
    }

    trainfile.close();

    ofstream testfile;
    testfile.open(testPath);

    for(unsigned int i = 0; i < testing.data.size(); ++i){
        Pattern p = testing.data.at(i);
        for(unsigned int j = 0; j < p.inputs.size(); ++ j)
            testfile << p.inputs.at(j) << " ";
        for( unsigned j = 0; j < p.outputs.size(); ++j)
            testfile << p.outputs.at(j) << " ";
        testfile << "\n";
    }
    testfile.close();

    ofstream valuesfile;
    valuesfile.open(normvaluesPath);

    for(unsigned int i = 0; i < ds.maxInputs.size(); ++i)
        valuesfile << ds.maxInputs.at(i) << " ";

    valuesfile << endl;

    for(unsigned int i = 0; i < ds.minInputs.size(); ++i)
        valuesfile << ds.minInputs.at(i) << " ";
    valuesfile << endl;
    for(unsigned int i = 0; i < ds.maxOutputs.size(); ++i)
        valuesfile << ds.maxOutputs.at(i) << " ";
    valuesfile << endl;
    for(unsigned int i = 0; i < ds.minOutputs.size(); ++i)
        valuesfile << ds.minOutputs.at(i) << " ";
    valuesfile.close();

    return 0;

}
