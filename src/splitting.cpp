// g++ splitting.cpp -o splitting

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdio>
using namespace std;


void print ( vector<int>& s ) {
    sort( s.begin(), s.end() );
    copy( s.begin(), s.end(), ostream_iterator<int>(cout, " ") );
    cout << endl;
}

int main( ) {
    // creo un array con un po' di roba dentro
    vector<int> whole;
    for ( int i = 0; i < 30; ++i ) whole.push_back( i );

    // il numero di partizioni, hai detto vuoi farlo deterministicamente
    int partitions = 6;


    int beg = 0, end = 0;
    for ( int i = partitions; i != 0; --i ) {
        beg = end; // la prima volta e' 0, quindi ok
        end = beg + (whole.size() - beg) / i; // il numero di elementi rimanenti diviso
                                              // le partizioni rimanenti
        
        vector<int> test;
        vector<int> train;
        for ( int j = 0; j < (int) whole.size(); ++j ) {
            if ( j >= beg && j < end )
                test.push_back( whole[j] );
            else
                train.push_back( whole[j] );
        }

        // splitto ulteriormente il TRAIN set in VALIDATION e TRAIN
        // commenta la prossima riga se vuoi evitare di prendere il validation a caso
        random_shuffle( train.begin(), train.end() );
        // prendo gli ultimi (train.size() / 4) elementi e li metto nel validation
        vector<int> validation( train.end() - train.size() / 4, train.end() );
        // poi li rimuovo dal TRAIN
        train.erase( train.end() - train.size() / 4, train.end() );

        cout << "TEST:  "; print( test );
        cout << "TRAIN: "; print( train );
        cout << "VALID: "; print( validation );
//        getchar();
    }
    
    return 0;
}
