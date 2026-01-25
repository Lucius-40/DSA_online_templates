#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define pb push_back
const int INF = 1e9;

struct Edge {
    int to, cap, flow, rev;
};

int n, m, k;
vector<vector<Edge>> adj;


void add_edge(int from, int to, int cap) {
    Edge forward = {to, cap, 0, (int)adj[to].size()};
    Edge backward = {from, 0, 0, (int)adj[from].size()};
    adj[from].push_back(forward);
    adj[to].push_back(backward);
}

int bfs(int s, int t, vector<int>& parent_node, vector<int>& parent_edge) {
    fill(parent_node.begin(), parent_node.end(), -1);
    parent_node[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int i = 0; i < adj[cur].size(); i++) {
            Edge &e = adj[cur][i];
            if (parent_node[e.to] == -1 && e.cap - e.flow > 0) {
                parent_node[e.to] = cur;
                parent_edge[e.to] = i;
                int new_flow = min(flow, e.cap - e.flow);
                if (e.to == t) return new_flow;
                q.push({e.to, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent_node(n + m + 2);
    vector<int> parent_edge(n + m + 2);
    int new_flow;

    while (new_flow = bfs(s, t, parent_node, parent_edge)) {
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
    
    cin >> n >> m>>k ;
    adj.assign(n + m + 2, vector<Edge>());
    int source = 0;
    int sink = n +m + 1;

    
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        add_edge(a , b + n, 1); 
    }

    for (int i = 1; i <= n; i++) {
        add_edge(source, i, 1);
    }

    for (int i = 1; i <= m; i++) {
        add_edge(i+n, sink, 1);
    }

    int ans = maxflow(source, sink);
    cout << ans << "\n";

    for (int i = 1; i <= n; i++) {
        for (auto &e : adj[i]) {
            if (e.to > n && e.to < sink && e.flow == 1) {
                cout << i << " " << e.to - n << "\n";
            }
        }
    }

    return 0;
}