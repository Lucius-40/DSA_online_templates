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

const int INF = 1e9;
const ll LINF = 1e18;

// Dijkstra's Algorithm - Single Source Shortest Path (O((V+E)logV))
// Works for graphs with NON-NEGATIVE edge weights only
void dijkstra(int s, vector<int>& d, vector<int>& p, vector<vector<pair<int, int>>>& adj) {
    // s -> source vertex
    // d -> distance array (output)
    // p -> predecessor array (output) - for path reconstruction
    // adj -> adjacency list: adj[u] = {{v, w}, ...} means edge u->v with weight w
    
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);
    
    priority_queue<pii, vector<pii>, greater<pii>> pq; // min-heap: {dist, vertex}
    d[s] = 0;
    pq.push({0, s});
    
    while (!pq.empty()) {
        auto [dist, v] = pq.top();
        pq.pop();
        
        if (dist > d[v]) continue; // already processed with better distance
        
        for (auto [to, len] : adj[v]) {
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                pq.push({d[to], to});
            }
        }
    }
}

// Reconstruct path from source to target using predecessor array
vector<int> getPath(int s, int t, vector<int>& p) {
    vector<int> path;
    for (int v = t; v != -1; v = p[v])
        path.pb(v);
    reverse(all(path));
    
    if (path[0] != s) return {}; // no path exists
    return path;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; // n = vertices, m = edges
    cin >> n >> m;
    
    vector<vector<pii>> adj(n); // 0-indexed vertices
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});      // directed edge
        // adj[v].pb({u, w});   // uncomment for undirected graph
    }
    
    int source = 0; // change as needed
    vi dist, parent;
    dijkstra(source, dist, parent, adj);
    
    // Print distances from source
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF)
            cout << "INF ";
        else
            cout << dist[i] << " ";
    }
    cout << "\n";
    
    // Example: Get path from source to vertex (n-1)
    // vector<int> path = getPath(source, n-1, parent);
    // if (!path.empty()) {
    //     for (int v : path) cout << v << " ";
    //     cout << "\n";
    // }
    
    return 0;
}