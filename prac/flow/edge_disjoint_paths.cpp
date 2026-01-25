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
#define vvi vector<vi>
#define vvpii vector<vector<pii>>
const int INF = 1e9;
const ll LINF = 1e18;

struct Edge {
    ll to, cap, flow, rev;
    bool id ;
};

vector<vector<Edge>> adj;

void add_edge(int from, int to, int cap) {
    Edge forward = {to, cap, 0, (int)adj[to].size(), true};
    Edge backward = {from, 0, 0, (int)adj[from].size(),false};
    adj[from].push_back(forward);
    adj[to].push_back(backward);
}


ll bfs(int s, int t, vector<int>& parent_edge, vector<int>& parent_node) {
    fill(parent_node.begin(), parent_node.end(), -1);
    parent_node[s] = -2;
    queue<pair<int, ll>> q;
    q.push({s, LINF});

    while (!q.empty()) {
        int v = q.front().first;
        ll flow = q.front().second;
        q.pop();

        for (int i = 0; i < adj[v].size(); i++) {
            Edge &e = adj[v][i];
            if (parent_node[e.to] == -1 && e.cap - e.flow > 0) {
                parent_node[e.to] = v;
                parent_edge[e.to] = i;
                ll new_flow = min(flow, e.cap - e.flow);
                if (e.to == t) return new_flow;
                q.push({e.to, new_flow});
            }
        }
    }
    return 0;
}


ll maxflow(int s, int t, int n) {
    ll flow = 0;
    vector<int> parent_edge(n);
    vector<int> parent_node(n);
    ll new_flow;

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

void find_paths(int s, int t, int n, vector<vector<int>>& paths) {
    // Extract paths by tracing flow in the residual graph
    while(true) {
        vector<int> parent(n, -1);
        vector<int> parent_edge(n, -1);
        queue<int> q;
        q.push(s);
        parent[s] = -2;
        
        bool found = false;
        while(!q.empty() && !found) {
            int v = q.front();
            q.pop();
            
            for(int i = 0; i < adj[v].size(); i++) {
                Edge& e = adj[v][i];
                // Follow edges with positive flow in the forward direction
                if(parent[e.to] == -1 && e.flow > 0 && e.id) {
                    parent[e.to] = v;
                    parent_edge[e.to] = i;
                    if(e.to == t) {
                        found = true;
                        break;
                    }
                    q.push(e.to);
                }
            }
        }
        
        if(!found) break;
        
        // Reconstruct the path from s to t
        vector<int> path;
        int cur = t;
        while(cur != s) {
            path.push_back(cur);
            int prev = parent[cur];
            int idx = parent_edge[cur];
            // Reduce flow by 1 to "consume" this path
            adj[prev][idx].flow--;
            cur = prev;
        }
        path.push_back(s);
        reverse(path.begin(), path.end());
        paths.push_back(path);
    }
}

void solve(){
    int n , m ;
    cin >> n >> m ;
    adj.clear();
    adj.resize(n);
    for(int i = 0 ;i < m ;i++){
        int a ,b ;
        cin >> a >> b ;
        a--;b--;
        add_edge(a,b,1);
        
    }

    ll ans = maxflow(0,n-1,n);
    cout << ans << "\n";
    
    // Find and print all edge-disjoint paths
    vector<vector<int>> paths;
    find_paths(0, n-1, n, paths);
    
    for(int i = 0; i < paths.size(); i++) {
        cout << "Path " << (i+1) << ": ";
        for(int j = 0; j < paths[i].size(); j++) {
            cout << (paths[i][j] + 1); // Convert back to 1-indexed
            if(j < paths[i].size() - 1) cout << " -> ";
        }
        cout << "\n";
    }
}

int main() {
    int t ;
    cin >> t ;
    while(t--)solve();    
    return 0;
}
