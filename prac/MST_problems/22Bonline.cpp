// #include "DSU.hpp" 

// using namespace DSU ;

// bool comp(Edge a , Edge b){
//     return a.weight < b.weight ;
// }

// int main(){
//     freopen("input.txt","r",stdin);
//     //freopen("output.txt","w",stdout);
    
//     int n , r ;
//     cin >> n >> r ;
//     init(n);
//     vector<Edge> edges ;
//     vector<pii> points ;
//     for(int i = 0 ; i < n ; i++){
//         int a , b;
//         cin >> a >> b ;
//         points.pb({a,b});
//     }
//     //int root ; cin >> root ;
//     for(int i = 0 ; i < n ; i++){
//         for(int j = i+1 ; j < n ; j++){
//             Edge e ;
//             int dx = points[i].F - points[j].F ;
//             int dy = points[i].S - points[j].S ;
//             int d = sqrt((dx*dx)+(dy*dy)) ;
//             e.u = i ;
//             e.v = j ;
//             e.weight = d ;
//             edges.pb(e);
//         }
//     }

//     sort(edges.begin(), edges.end(), comp);

//     vector<Edge> mst ;
//     ll cost = 0 ;
//     int rail, road ;
//     rail = 0 ; road = 0 ;int road_c = 0 ;
//     for(auto e : edges){
//         if(find_set(e.u)!= find_set(e.v)){
//             mst.pb(e);
//             cost += e.weight ;
//             union_set(e.u, e.v);
//             if(e.weight <= r){
//                 road += e.weight ;
//             }
//             else {rail += e.weight; road_c++;} ;
//         }
//     }

//     cout <<road_c +1<<" " <<road <<" "<< rail<< endl ;
    
    



// }

#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define pii pair<int,int>
#define vi vector<int>
#define vll vector<ll>
#define pb push_back
#define all(x) x.begin(), x.end()
#define F first
#define S second

const ll INF = 1e15;


struct Edge {
    int u;
    int v;
    int weight;
};

class DSU {
private:
    vector<int> parent;
    vector<int> rank;
    int n;

public:
    // Constructor
    DSU(int size) : n(size) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find with path compression
    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    // Union by rank
    void union_set(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }

    // Reset the DSU
    void reset() {
        rank.assign(n, 0);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
};



bool comp(Edge a, Edge b){
   return a.weight < b.weight;
}


int main(){
    freopen("input2.txt", "r", stdin);
    int n, r ;
    cin >> n >>r;
    vector<pii>points(n) ;
    for(int i = 0 ; i < n ; i++){
        cin >> points[i].F >> points[i].S ;
    } 


    vector<Edge> edges ;
    for(int i = 0 ; i < n ; i++){
        for(int j = i+1 ; j < n ; j++){
            Edge e ;
            int dx = points[i].F - points[j].F ;
            int dy = points[i].S - points[j].S ;
            int d = sqrt((dx*dx)+(dy*dy)) ;
            e.u = i ;
            e.v = j ;
            e.weight = d ;
            edges.pb(e);
        }
    }

    sort(edges.begin(), edges.end(), comp);
    DSU dsu(n);
    int rail_used=0, road=0, rail=0 ;
    for(int i = 0 ; i < edges.size(); i++){
        if(dsu.find_set(edges[i].u)!= dsu.find_set(edges[i].v)){
            dsu.union_set(edges[i].u, edges[i].v);
            if(edges[i].weight > r){
                rail_used ++ ;
                rail+= edges[i].weight ;
            }
            else road += edges[i].weight;
        }

    }


    cout << rail_used + 1 <<" "<< road <<" "<<rail<< endl ;
}