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
#define vvpii vector<vector<pair<int, int>>>
const int INF = 1e9;
const ll LINF = 1e18;



class Solution {
    const int m = 1e9 + 7 ;
   int dijkstra(int s, vector<int> & d, vector<int> & p, vvpii& adj) {
    //s-> source, d -> distance
    //p -> predecessor
    // adjancency list is stored like:
    // adj[u] == {v,w} ; there is an edge (u,v) of weight w
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);
    vi ways(n,0);
    ways[0] = 1 ;

    priority_queue<pii, vector<pii>, greater<pii>> pq; // creeates min priority queue of pairs 
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

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                pq.push({d[to], to});
            }
            if(d[v] < d[to]){
                ways[to] += ways[v];
            }
        }
    }
    return ways[n-1];
}


vi d ;

public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        vvpii adj(n);
        for(int i = 0 ; i < edges.size(); i++){
            adj[edges[i][0]-1].pb({edges[i][1]-1, edges[i][2] });
            adj[edges[i][1]-1].pb({edges[i][0]-1, edges[i][2] });
        }
        vi  p(n);
        d.assign(n, INF);
        return  dijkstra(0, d, p , adj);

    }
};