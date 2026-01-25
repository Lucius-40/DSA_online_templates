#include<bits/stdc++.h>
using namespace std ;
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

int n;
int m ;
vector<vi> capacity;
vector<vi> original_capacity; 
vector<vi> adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;
    
    // Save original capacities
    original_capacity = capacity;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}


int main(){
    cin >> n>> m ;
    capacity.assign(n,vector<int>(n,0));
    adj.assign(n,vector<int>());
    for(int i = 0 ;i < m ; i++){
        int a , b, c;
        cin >> a >> b >> c ;
        adj[a].pb(b);
        capacity[a][b]= c ;
    }
    int source , sink ;
    cin >> source >> sink ;
    int ans = maxflow(source,sink);
    cout << ans << endl ;

    for (int i = 0; i < n; i++) {
        for (int v : adj[i]) {
            int edge_flow = original_capacity[i][v] - capacity[i][v];
            if (original_capacity[i][v] > 0) {
                cout << i << " " << v << " " << edge_flow 
                     << "/" << original_capacity[i][v] << "\n";
            }
        }
    }

    return 0 ;

}