#include<bits/stdc++.h>
#include "hash1.hpp"
#include "hash2.hpp"
#include "utils.hpp"

using namespace std;

int main(){
    int n , m ;
    cin >> n >> m ;
    Hash1Impl :: HashTable_Chaining<string , int> set ;
    vector<string> unique ;
    string s ;
    cin >> s ;
    for(int i = 0 ; i < n; i++){
        string temp = "";
        int start = i ;
        int end = (i + m -1)%n ;
        int k = start ;
        for(int j = 0 ; j < m ; j++){
            
            temp.push_back(s[k]);
            k = (k+1) % n ; 
        }
        int before_count = 0 ;
        bool exists = set.search(temp, before_count);
        if(exists){
            set.update(temp, before_count+1);
        }
        else {
            set.insert(temp, 1);
            unique.push_back(temp);
        }
    }

    for(int i = 0 ; i < unique.size(); i++){
        cout << unique[i]<<" ";
        int count ;
        set.search(unique[i], count);
        cout << count <<endl ;
    }



}