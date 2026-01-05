#include<bits/stdc++.h>
using namespace std ;
#define ll long long int
const ll INF =1e18 ;



void dijkstra(int s, vector<ll> & d, vector<vector<pair<int, ll>>>& adj) {
    
    int n = adj.size();
    d.assign(n, INF);
   

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq; // creeates min priority queue of pairs 
    
    d[s] = 0;
    pq.push({0, s}); // {distance, vertex}
    
    while (!pq.empty()) {
        ll dist = pq.top().first;
        int v = pq.top().second;
        pq.pop();
        
        if (dist > d[v])
            continue;
        
        for (auto edge : adj[v]) {
            int to = edge.first;
            ll len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                pq.push({d[to], to});
            }
        }
    }
}



int main(){
    int n , m ;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> adj(n);
    map<pair<int,int> , ll> weights ;
    vector<ll>  d(n) ;
    vector<vector<pair<int,ll>>> adj_reversed(n);
    vector<ll>  d_reversed(n) ;
    for(int i = 0 ; i < m ; i++){
        int a , b ;ll w;
        cin >> a >> b >> w ;
        adj[a-1].push_back(make_pair(b-1,w));
        weights[make_pair(a-1,b-1)] = w ;
        adj_reversed[b-1].push_back(make_pair(a-1, w));
        
    }
    dijkstra(0,d,adj);
    dijkstra(n-1,d_reversed, adj_reversed);
    ll answer = d[n-1] ;
    for( auto& p : weights){
        ll opt = d[p.first.first] + (p.second / 2 ) + d_reversed[p.first.second];
        if(opt < answer) answer = opt ;
    }
    
    cout << answer ;
    
    
}