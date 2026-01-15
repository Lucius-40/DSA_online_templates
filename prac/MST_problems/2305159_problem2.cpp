#include<bits/stdc++.h>
#define ll long long int
#define pii pair<int,int>
#define vi vector<int>
#define vll vector<ll>
#define pb push_back
#define all(x) x.begin(), x.end()
#define F first
#define S second
#define vvi vector<vi>
#define vvpii vector<vector<pii>>
const int INF = 1e9;
const ll LINF = 1e18;

using namespace std ;

struct Edge{
    int a ;
    int b ;
};

ll mst_prim(int n, int s ,vvpii &adj, vector<Edge>&  mst){
    priority_queue<vi, vector<vi>,greater<vi>> pq;
    vector<bool> visited(n, false);
    ll res = 0 ;
    // Start from node 0
    pq.push({0, s, -1});
    

    while(!pq.empty()) {

        vi p = pq.top();
        pq.pop();

        int wt = p[0];
        int u = p[1];
        int parent = p[2];

        if(visited[u])
            continue;
       
        if(parent != -1){
            Edge e ;
            e.a = parent;
            e.b = u ;
            mst.pb(e);
        }
        res += wt;
        visited[u] = true;

        // Push adjacent edges
        for(auto &v : adj[u]) {

            if(!visited[v.F]) {
                pq.push({v.S, v.F,u});
            }
        }
    }

    return res;
}


int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n , m ;
    cin >> n >> m ;
    vvpii adj(n) ;
    vector<Edge> mst ;
    for(int i = 0 ; i < m ; i++){
        int a , b, c ;
        cin >> a >> b >> c ;
        adj[a].pb({b,c});
        adj[b].pb({a,c});
    }
    int root ; cin >> root ;
    ll ans = mst_prim(n,root,adj,mst);
    
    cout <<"Total weight " <<ans << endl ;
    cout <<"Root node "<< root << endl ;
    for(auto e : mst){
        cout << e.a <<" "<<e.b<<endl ;
    }
}



