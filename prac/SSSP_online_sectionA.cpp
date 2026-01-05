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
const int INF = 1e9;
const ll LINF = 1e18;

bool comp(pii a , pii b ){
    return a.S < b.S ;
}

// Dijkstra's Algorithm - Single Source Shortest Path (O((V+E)logV))
// Works for graphs with NON-NEGATIVE edge weights only
vector<pii> dijkstra(int s, vector<int>& d, vector<int>& p, vector<vector<pair<int, int>>>& adj) {
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
    vector<pii> node_dist_pair ;

    for(int i = 0 ; i < d.size(); i++){
        node_dist_pair.pb({i, d[i]});
    }
    sort(node_dist_pair.begin(), node_dist_pair.end(), comp);
    return node_dist_pair ;
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("inputA.txt", "r", stdin);
    //freopen("outputA.txt", "w", stdout);
    
    int n, m, fee; // n = vertices, m = edges
    cin >> n >> m>> fee;
    vi capacity(n) ;
    for(int i = 0 ; i < n ; i++){
         cin >> capacity[i];
    }
    int stu ;
    
    vi d(n), p(n);
    vector<vector<pii>> adj(n);
    
    for(int i = 0 ; i < m ; i++){
        int a ,b ,c ;
        cin >> a >> b >> c ;
        a-- ;
        b-- ;
        adj[a].pb({b, c});
        adj[b].pb({a,c});
    }
    cin >> stu ;
    vector<pii> labs = dijkstra(0, d, p , adj);
    int lab = 0 ;
    for(int i = 0 ; i < stu ; i++){
        while(lab < n and capacity[labs[lab].F] <= 0){
            lab ++ ;
        }
        if(lab >= n){
            cout << -1 <<' ';
        }
        else {
            cout << labs[lab].S + fee << endl;
            capacity[labs[lab].F]--;
        }
    }

}