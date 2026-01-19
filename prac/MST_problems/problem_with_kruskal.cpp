#include "DSU.hpp" 

using namespace DSU ;

bool comp(Edge a , Edge b){
    return a.weight < b.weight ;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n , m ;
    cin >> n >> m ;
    init(n);
    vector<Edge> edges(m) ;
    for(int i = 0 ; i < m ; i++){
        int a , b, c ;
        cin >> edges[i].u >> edges[i].v >> edges[i].weight ;
    }
    int root ; cin >> root ;

    sort(edges.begin(), edges.end(), comp);

    vector<Edge> mst ;
    ll cost = 0 ;
    for(auto e : edges){
        if(find_set(e.u)!= find_set(e.v)){
            mst.pb(e);
            cost += e.weight ;
            union_set(e.u, e.v);
        }
    }

    cout <<"Total weight " <<cost << endl ;
    for(auto e : mst){
        cout << e.u <<" "<<e.v<<endl ;
    }
    
}