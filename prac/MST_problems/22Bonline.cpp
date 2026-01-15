#include "DSU.hpp" 

using namespace DSU ;

bool comp(Edge a , Edge b){
    return a.weight < b.weight ;
}

int main(){
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    
    int n , r ;
    cin >> n >> r ;
    init(n);
    vector<Edge> edges ;
    vector<pii> points ;
    for(int i = 0 ; i < n ; i++){
        int a , b;
        cin >> a >> b ;
        points.pb({a,b});
    }
    //int root ; cin >> root ;
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

    vector<Edge> mst ;
    ll cost = 0 ;
    int rail, road ;
    rail = 0 ; road = 0 ;int road_c = 0 ;
    for(auto e : edges){
        if(find_set(e.u)!= find_set(e.v)){
            mst.pb(e);
            cost += e.weight ;
            union_set(e.u, e.v);
            if(e.weight <= r){
                road += e.weight ;
            }
            else {rail += e.weight; road_c++;} ;
        }
    }

    cout <<road_c +1<<" " <<road <<" "<< rail<< endl ;
    
    



}