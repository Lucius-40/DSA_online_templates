#include<bits/stdc++.h>
#include "hash1.hpp"
#include "hash2.hpp"
#include "utils.hpp"

using namespace std;
struct person{
    string name ;
    string nid ;
    string phone_number ;
};

int main(){
    int action ;
    Hash1Impl :: HashTable_Chaining<string, person* > nid;
    Hash1Impl :: HashTable_Chaining<string, person* > name;
    Hash1Impl :: HashTable_Chaining<string, person* > mobile;
    while(true){
        cout << "Enter Action : \n";
        cin >> action ;
        getchar();
        if(action != 1 and action != 2)break ;
        if(action == 1){
            //insert op
            string names , mobiles , nids ;
            cout << "Enter Name : ";
            getline(cin, names);
            cout << "\nEnter NID  :";
            getline(cin, nids);
            cout << "\nEnter mobile number : ";
            getline(cin, mobiles);
            bool exists1, exists2,exists3 ;
            
            exists1 = exists2 = exists3 = false ;
            person* temp = nullptr ;
            exists1 = nid.search(nids, temp);
            exists2 = name.search(names, temp);
            exists3 = mobile.search(mobiles, temp);
            if(!exists1 and !exists2 and !exists3 ){
                temp = new person ;
                temp->name = names ;
                temp->nid = nids ;
                temp->phone_number = mobiles;
                nid.insert(nids, temp);
                name.insert(names, temp);
                mobile.insert(mobiles, temp);
            }
            else continue;

        }
        else {
            cout << "Enter string ";
            string names ;
            getline(cin, names);
            bool exists1, exists2,exists3 ;
            exists1 = exists2 = exists3 = false ;
            person* temp = nullptr ;
            exists1 = nid.search(names, temp);
            if(!exists1)exists2 = name.search(names, temp);
            if(!exists2)exists3 = mobile.search(names, temp);
            if(temp) {
                cout <<"Match Found\n";
                cout << "Name : "<<temp->name<<endl ;
                cout << "NID : "<<temp->nid<<endl ;
                cout << "Mobile : "<<temp->phone_number<<endl ;
            }
            else{
                cout <<"No match found\n";
            }

        }
    }
}