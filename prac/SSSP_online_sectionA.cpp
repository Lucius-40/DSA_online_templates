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

vector<int> restore_path(int s, int t, vector<int> const& p) {
    vector<int> path;

    for (int v = t; v != s; v = p[v])
        path.push_back(v);
    path.push_back(s);

    reverse(path.begin(), path.end());
    return path;
}

void dijkstra(int k , int dest,int s, vi & d, vi & p, vector<vector<pair<int, int>>>& adj) {
    //s-> source, d -> distance
    //p -> predecessor
    // adjancency list is stored like:
    // adj[u] == {v,w} ; there is an edge (u,v) of weight w
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // creeates min priority queue of pairs 
    // pairs are in the form : {distance, vertex}
    d[s] = 0;
    pq.push({0, s});
    
    while (!pq.empty()) {
        int dist = pq.top().first;
        int v = pq.top().second;
        pq.pop();
        
        if (dist > d[v])
            continue;
        
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;
            int extra = (v == s)? 0 : k ;
            len += extra ;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                pq.push({d[to], to});
            }
        }
    }
    vi path = restore_path(s,dest,p);
    for(int x : path) cout << x+1 << "-> ";
    cout << d[dest]; 
    
}

int main(){
    int k ,n , m ;
    cin >> k >> n >> m ;
    vvpii adj(n);
    vi d(n), p(n);
    for(int i = 0 ; i < m ;i++){
        int a , b , c ,d ;
        cin >> a >> b >> c >> d ;
        a-- ; b-- ;
        adj[a].pb({b, d + (k*c)});
        adj[b].pb({a, d + (k*c)});
    }
    int s ,dest ;
    cin >>s >> dest ;
    dijkstra(k, dest-1,s-1,d,p,adj);
}