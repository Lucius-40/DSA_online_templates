#include<bits/stdc++.h>
#include "hash1.hpp"
#include "hash2.hpp"
#include "utils.hpp"

using namespace std;


int main(){
    int n , m ;
    cin >> n >> m ;
    Hash1Impl :: HashTable_Chaining<string , bool> set ;
    for(int i = 0  ; i < n ; i++){
        string input ;
        cin >> input ;
        if(i==0){
            set.insert(input, true);
        }
        string complement ;
        complement = input ;
        for(int j  = 0 ; j < m ; j++){
            switch(complement[j]){
                case 'A':
                    complement[j]='T';
                    break ;
                case 'T':
                    complement[j]='A';
                    break;
                case 'G':
                    complement[j]='C';
                    break ;
                case 'C':
                    complement[j]='G';
                    break ;
                default :
                    break ;
            }
        }
        reverse(complement.begin(), complement.end());
        bool poodle ;
        bool exists = set.search(complement,poodle );
        if(exists){
            cout << complement <<" "<<input <<endl;
        }
        set.insert(input, true);

    }

}