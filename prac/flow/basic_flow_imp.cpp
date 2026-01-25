#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cap, flow, rev;
};

vector<vector<Edge>> adj;


bool bfs(int s, int t, vector<int>& parent_edge, vector<int>& parent_node) {
    fill(parent_node.begin(), parent_node.end(), -1);
    parent_node[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, 1e9});

    while (!q.empty()) {
        int v = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int i = 0; i < adj[v].size(); i++) {
            Edge &e = adj[v][i];
            if (parent_node[e.to] == -1 && e.cap - e.flow > 0) {
                parent_node[e.to] = v;
                parent_edge[e.to] = i;
                int new_flow = min(flow, e.cap - e.flow);
                if (e.to == t) return new_flow;
                q.push({e.to, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(int s, int t, int n) {
    int flow = 0;
    vector<int> parent_edge(n);
    vector<int> parent_node(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent_edge, parent_node)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent_node[cur];
            int idx = parent_edge[cur];
            adj[prev][idx].flow += new_flow;
            int rev_idx = adj[prev][idx].rev;
            adj[cur][rev_idx].flow -= new_flow;
            cur = prev;
        }
    }
    return flow;
}

int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n, m;
    cin >> n >> m;
    adj.assign(n, vector<Edge>());

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c, 0, (int)adj[v].size()});
        adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
       
    }

    int source, sink;
    cin >> source >> sink;
    cout <<  maxflow(source, sink, n) << endl;

    for (int i = 0; i < n; i++) {
        for (auto &e : adj[i]) {
            
            if (e.cap > 0) {
                cout << i << " " << e.to << " " << e.flow << "/" << e.cap << endl;
            }
        }
    }
    return 0;
}