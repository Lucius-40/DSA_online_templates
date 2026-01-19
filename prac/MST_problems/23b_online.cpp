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
        
        cin >> edges[i].u >> edges[i].v >> edges[i].weight ;
        edges[i].u -- ; edges[i].v -- ;
    }
    

    sort(edges.begin(), edges.end(), comp);

    // vector<Edge> mst ;
    ll cost = 0 ;
    int ans = INT32_MAX ;
    for(int i = 0 ; i < edges.size(); i++){
        int count = 0 ;
        init(n);
        for(int j = i ; j < edges.size(); j++){
            if(find_set(edges[j].u)!= find_set(edges[j].v) ){
                union_set(edges[j].u, edges[j].v);
                count ++ ;
            }
            if(count == n-1){
                ans = min(ans, abs(edges[i].weight- edges[j].weight));
                break ;
            }
        }
    }

    cout << ans << endl ;
    
}