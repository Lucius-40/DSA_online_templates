#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define pii pair<int,int>
#define vi vector<int>
#define vll vector<ll>
#define pb push_back
#define all(x) x.begin(), x.end()
#define F first
#define S second

namespace DSU{
    int largest_set =0;
    int largest_size = 1 ;
    int components = -1 ;

    struct Edge {
        int u;
        int v;
        int weight;
    };

    vi set, size;

    void make_set(int v){
        set[v]=v ;
        size[v]= 1 ;
    }
    int find_set(int v) {
        if (v == set[v])
            return v;
        return set[v] = find_set(set[v]);
    }

    void union_set(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b]){
                set[a] = b;
                size[b]+= size[a];
                if(size[b] > largest_size){
                    largest_size = size[b];
                    largest_set = b ;
                }
                
            }
            else {
                set[b]=a ;
                size[a]+=size[b];
                if(size[a] > largest_size){
                    largest_size = size[a];
                    largest_set = a ;
                }
            }
            components-- ;
        }
    }

    

    void init(int n){
        set.resize(n);
        size.resize(n);
        components=n ;
        for(int i= 0 ; i < n ; i++)
            make_set(i);
    }
}
using namespace DSU ;
bool comp(Edge a , Edge b){
    return a.weight < b.weight ;
}

int main(){
    
    int n , m ;
    cin >> n >> m ;
    init(n);
    for(int i = 0 ; i < m ; i++){
        int a ,b ;
        cin >> a >> b ;
        a--;b--;
        union_set(a,b);
        cout<<components << " "<< largest_size <<endl ;
    }
    
}
