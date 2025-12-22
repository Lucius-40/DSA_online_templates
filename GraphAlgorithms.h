#pragma once
#include <bits/stdc++.h>
using namespace std;

// Macros
#define ll long long int
#define pii pair<int,int>
#define vi vector<int>
#define vll vector<ll>
#define pb push_back
#define all(x) x.begin(), x.end()
#define F first
#define S second

namespace GraphAlgo {

    const int INF = 1e9;
    const ll LINF = 1e18;

    // Edge structure for Bellman-Ford
    struct Edge {
        int a, b, cost;
    };

    // ==================== DIJKSTRA'S ALGORITHM ====================
    // Single Source Shortest Path (O((V+E)logV))
    // Works for NON-NEGATIVE edge weights only
    void dijkstra(int s, vector<int>& d, vector<int>& p, vector<vector<pii>>& adj) {
        int n = adj.size();
        d.assign(n, INF);
        p.assign(n, -1);
        
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        d[s] = 0;
        pq.push({0, s});
        
        while (!pq.empty()) {
            auto [dist, v] = pq.top();
            pq.pop();
            
            if (dist > d[v]) continue;
            
            for (auto [to, len] : adj[v]) {
                if (d[v] + len < d[to]) {
                    d[to] = d[v] + len;
                    p[to] = v;
                    pq.push({d[to], to});
                }
            }
        }
    }

    // ==================== BELLMAN-FORD ALGORITHM ====================
    // Single Source Shortest Path (O(VE))
    // Works with NEGATIVE edge weights, detects negative cycles
    void bellmanFord(int n, int v, vector<Edge>& edges, vector<int>& d, vector<int>& p) {
        d.assign(n, INF);
        p.assign(n, -1);
        d[v] = 0;
        
        for (int i = 0; i < n - 1; ++i) {
            bool any_update = false;
            vector<int> d_prev = d;
            for (Edge e : edges) {
                if (d_prev[e.a] < INF) {
                    if (d[e.b] > d_prev[e.a] + e.cost) {
                        d[e.b] = max(-INF, d_prev[e.a] + e.cost);
                        p[e.b] = e.a;
                        any_update = true;
                    }
                }
            }
            if (!any_update) break; // Early stop if no relaxation
        }
    }

    // Detect negative cycle using Bellman-Ford
    bool detectNegativeCycle(int n, int v, vector<Edge>& edges) {
        vector<int> d(n, INF);
        vector<int> p(n, -1);
        d[v] = 0;
        int x = -1;
        
        for (int i = 0; i < n; ++i) {
            x = -1;
            vector<int> d_prev = d;
            for (Edge e : edges) {
                if (d_prev[e.a] < INF) {
                    if (d[e.b] > d_prev[e.a] + e.cost) {
                        d[e.b] = max(-INF, d_prev[e.a] + e.cost);
                        p[e.b] = e.a;
                        x = e.b;
                    }
                }
            }
        }

        if (x == -1)
            return false;
        else {
            int y = x;
            for (int i = 0; i < n; ++i)
                y = p[y];

            vector<int> path;
            for (int cur = y;; cur = p[cur]) {
                path.push_back(cur);
                if (cur == y && path.size() > 1)
                    break;
            }
            reverse(path.begin(), path.end());
            path.pop_back();

            cout << "Negative cycle: ";
            for (int u : path)
                cout << u + 1 << " ";
            cout << "\n";
            return true;
        }
    }

    // ==================== BFS ALGORITHM ====================
    // Breadth-First Search (O(V+E))
    // Shortest path in unweighted graphs
    void bfs(int s, vector<vector<int>>& adj, vector<bool>& used, vector<int>& d, vector<int>& p) {
        int n = adj.size();
        used.assign(n, false);
        d.assign(n, -1);
        p.assign(n, -1);
        
        queue<int> q;
        q.push(s);
        used[s] = true;
        d[s] = 0;
        
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : adj[v]) {
                if (!used[u]) {
                    used[u] = true;
                    q.push(u);
                    d[u] = d[v] + 1;
                    p[u] = v;
                }
            }
        }
    }

    // ==================== DFS ALGORITHM ====================
    // Depth-First Search (O(V+E))
    void dfs(int v, vector<vector<int>>& adj, vector<int>& color, vector<int>& time_in, vector<int>& time_out, int& timer) {
        time_in[v] = timer++;
        color[v] = 1; // gray (visiting)
        
        for (int u : adj[v]) {
            if (color[u] == 0) // white (unvisited)
                dfs(u, adj, color, time_in, time_out, timer);
        }
        
        color[v] = 2; // black (visited)
        time_out[v] = timer++;
    }

    // Initialize and run DFS on all vertices
    void runDFS(int n, vector<vector<int>>& adj, vector<int>& color, vector<int>& time_in, vector<int>& time_out) {
        color.assign(n, 0);
        time_in.assign(n, 0);
        time_out.assign(n, 0);
        int timer = 0;
        
        for (int i = 0; i < n; i++) {
            if (color[i] == 0)
                dfs(i, adj, color, time_in, time_out, timer);
        }
    }

    // ==================== PATH RECONSTRUCTION ====================
    // Reconstruct path from source to target using predecessor array
    vector<int> getPath(int s, int t, vector<int>& p) {
        vector<int> path;
        for (int v = t; v != -1; v = p[v])
            path.pb(v);
        reverse(all(path));
        
        if (path[0] != s) return {}; // no path exists
        return path;
    }

} // namespace GraphAlgo
