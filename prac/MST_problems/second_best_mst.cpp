#include <bits/stdc++.h>

using namespace std;

class DSU {
public:
    vector<int> p, r;
    
    // initially each node is its own parent
    DSU(int n) : p(n), r(n, 0) {
        for (int i = 0; i < n; i++) p[i] = i;   
    }
    
    // path compression
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);   
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        
        // already connected
        if (a == b) return false;                  
        
        // union by rank
        if (r[a] < r[b]) swap(a, b);                
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

// run kruskal while skipping one MST edge
int kruskal(int n, vector<array<int,3>> &edges, int skipU, int skipV) {
    DSU dsu(n);
    int cost = 0, used = 0;

    for (auto &e : edges) {
        int u = e[0], v = e[1], w = e[2];

        // ignore the chosen MST edge
        if ((u == skipU && v == skipV) || (u == skipV && v == skipU))
            continue;

        if (dsu.unite(u, v)) {
            cost += w;
            used++;
        }
    }
    
    // not a valid tree
    if (used != n - 1) return INT_MAX;    
    return cost;
}

int secondBestMST(vector<vector<pair<int,int>>> &adj) {
    int n = adj.size();

    // convert adjacency list to edge list
    vector<array<int,3>> edges;
    for (int u = 0; u < n; u++) {
        for (auto &p : adj[u]) {
            int v = p.first, w = p.second;
            
            // avoid duplicate undirected edges
            if (u < v) edges.push_back({u, v, w});  
        }
    }

    // sort edges by weight once
    sort(edges.begin(), edges.end(),
         [](auto &a, auto &b){ return a[2] < b[2]; });

    // build the MST
    DSU dsu(n);
    int mstCost = 0;
    vector<array<int,3>> mstEdges;

    for (auto &e : edges) {
        if (dsu.unite(e[0], e[1])) {
            mstCost += e[2];
            mstEdges.push_back(e);
        }
    }

    // try removing each MST edge to find second best
    int secondBest = INT_MAX;

    for (auto &e : mstEdges) {
        int newCost = kruskal(n, edges, e[0], e[1]);
        if (newCost > mstCost && newCost < secondBest)
            secondBest = newCost;
    }
    
    return secondBest == INT_MAX ? -1 : secondBest;
}

int main() {

    vector<vector<pair<int,int>>> adj = {
        {{1,4},{2,3}},
        {{0,4},{2,1},{3,5}},
        {{0,3},{1,1},{3,7},{4,10}},
        {{1,5},{2,7},{4,2}},
        {{2,10},{3,2}}
    };

    cout << secondBestMST(adj) << "\n";

    return 0;
}