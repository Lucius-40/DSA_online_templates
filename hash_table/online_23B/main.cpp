#include<bits/stdc++.h>
#include "hash1.hpp"
#include "hash2.hpp"
#include "utils.hpp"

using namespace std;

int main(){
    const int NUM_INSERTIONS = 10000;
    //const int NUM_SEARCHES = 1000;
    
    
    vector<string> keys = generate_unique_words(NUM_INSERTIONS, 10);
    
    random_device rd;
    mt19937 gen(42); 
    shuffle(keys.begin(), keys.end(), gen);

    Hash2Impl::HashTable_CustomProbing<string, int> h2_custom;
    for (int i = 0; i < keys.size(); i++) {
        h2_custom.insert(keys[i], i + 1);
    }

    int N ;
    cin >> N ;
    for(int i = 0 ; i < N ; i++){
        string s ;
        cin >> s ;
        h2_custom.display_probe_sequence(s);
        cout << endl ;
    }

    
    
}