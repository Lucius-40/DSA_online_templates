#include<bits/stdc++.h>
using namespace std ;
#define ll long long int
#define pii pair<int,int>
#define vi vector<int>
#define vll vector<ll>
#define pb push_back
#define all(x) x.begin(), x.end()
#define F first
#define S second
#define vvi vector<vi>
const int INF = 1e9;
const ll LINF = 1e18;


class Solution {
    
    void dijkstra(int s, vector<int> & d, vector<int> & p, vector<vector<pair<int, int>>>& adj, vector<int>& disappear) {
    //s-> source, d -> distance
    //p -> predecessor
    // adjancency list is stored like:
    // adj[u] == {v,w} ; there is an edge (u,v) of weight w
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // creeates min priority queue of pairs 
    // pairs are in the form : {distance, vertex}
    d[s] = 0;
    pq.push({0, s});
    
    while (!pq.empty()) {
        int dist = pq.top().first;
        int v = pq.top().second;
        pq.pop();
        
        if (dist > d[v])
            continue;
        
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to] and d[v] + len < disappear[to] ) {
                d[to] = d[v] + len;
                p[to] = v;
                pq.push({d[to], to});
            }
        }
    }
}
    public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        vector<vector<pii>> adj(n);
        for(int i = 0 ; i < edges.size(); i++){
            adj[edges[i][0]].pb({edges[i][1],edges[i][2]});
            adj[edges[i][1]].pb({edges[i][0],edges[i][2]});
        }
        vi d(n), p(n);

        dijkstra(0,d,p,adj,disappear);
        for(int i = 0 ; i< d.size(); i++){
            if(d[i] == INF){
                d[i] = -1 ;
            }
        }
        return d ;
    }
};