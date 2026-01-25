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
vector<bool> dfs_visit ;

void add_edge(int from, int to, int cap) {
    Edge forward = {to, cap, 0, (int)adj[to].size(), true};
    Edge backward = {from, 0, 0, (int)adj[from].size(),false};
    adj[from].push_back(forward);
    adj[to].push_back(backward);
}


void dfs(int s){
    if(dfs_visit[s])return ;
    dfs_visit[s]= true ;
    for(int i=0 ; i < adj[s].size(); i++){
        Edge e = adj[s][i];
        if(e.cap - e.flow > 0){
            if(dfs_visit[e.to])continue;
            dfs(e.to);
        }
    }

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

int main() {
    int n, m;
    cin >> n >> m;
    adj.assign(n, vector<Edge>());
    dfs_visit.assign(n,false);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v ;
        add_edge(u-1, v-1, 1);
        add_edge(v-1, u-1,1);
    }

    maxflow(0, n-1, n) ;
    dfs(0);
    vector<pair<int,int>>ans ;
   
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < adj[i].size(); j++){
            Edge e = adj[i][j];
            int dest = e.to ;
            if(e.id && dfs_visit[dest]== false && dfs_visit[i]==true)
                ans.push_back({i+1, dest+1});
        }
    }
    
    cout << ans.size()<<endl ;
    for(auto& e : ans){
        cout << e.first << " "<<e.second<<endl ;
    }


    
    return 0;
}