#include<bits/stdc++.h>
using namespace std ;
#define ll long long int 
const int INF = 1000000000;
#define pii pair<int,int>

void dijkstra(int s, vector<int> & d, vector<int> & p, vector<vector<pair<int, int>>>& adj) {
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

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                pq.push({d[to], to});
            }
        }
    }
}