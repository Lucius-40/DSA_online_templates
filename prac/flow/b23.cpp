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
    int to, cap, flow, rev;
};

vector<vector<Edge>> adj;


bool bfs(int s, int t, vector<int>& parent_edge, vector<int>& parent_node,vector<vector<Edge>>& adj) {
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

int maxflow(int s, int t, int n, vector<vector<Edge>>& adj) {
    int flow = 0;
    vector<int> parent_edge(n);
    vector<int> parent_node(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent_edge, parent_node,adj)) {
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
        u--; v--;
        adj[u].push_back({v, c, 0, (int)adj[v].size()});
        adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
       
    }

    int projects;
    cin >> projects;
    vi proj(projects,0);

    for(int i = 0 ; i < projects ; i++){
        vector<vector<Edge>> cop = adj ;
        int a , b,c ;
        cin >>a >> b >> c ;
        a-- ; b-- ;
        cop[a].push_back({b, c, 0, (int)cop[b].size()});
        cop[b].push_back({a, 0, 0, (int)cop[a].size() - 1});

        proj[i]= maxflow(0,n-1,n,cop);
        cout << "flow : "<<proj[i]<<endl ;

    }

    int ma = INT32_MIN;
    for(int x : proj)ma= max(x,ma);
    for(int i = 0 ; i < projects ; i++){
        if(proj[i]==ma){
            cout << i + 1 <<endl ;
        }
    }
}