#include<bits/stdc++.h>
using namespace std ;

struct Edge {
    int a, b, cost;
};


vector<Edge> edges;
const int INF = 1000000000;


void bellmanFord(int n, int v, vector<int>& ans)
{
    
    vector<int> d(n, INF);
    d[v] = 0;
    vector<int> p(n, -1);
    
    for (int i = 0; i < n-1; ++i) {
       
        vector<int> d_prev = d ;
        for (Edge e : edges)
            if (d_prev[e.a] < INF)
                if (d[e.b] > d_prev[e.a] + e.cost) {
                    d[e.b] = max(-INF, d_prev[e.a] + e.cost);
                    p[e.b] = e.a;
                   
                }
    }
    ans = d ;

    
}

bool detect_negative_cycle(int n, int v)
{
    // for n nodes from source v , checks for cycyle
    vector<int> d(n, INF);
    d[v] = 0;
    vector<int> p(n, -1);
    int x;
    for (int i = 0; i < n; ++i) {
        x = -1;
        vector<int> d_prev = d ;
        for (Edge e : edges)
            if (d_prev[e.a] < INF)
                if (d[e.b] > d_prev[e.a] + e.cost) {
                    d[e.b] = max(-INF, d_prev[e.a] + e.cost);
                    p[e.b] = e.a;
                    x = e.b;
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
            cout << u+1 << " ";
        return false ;
    }
}