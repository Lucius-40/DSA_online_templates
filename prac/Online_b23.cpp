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

struct State {
    ll dist;
    int node;
    int coupon;
    
    bool operator>(const State& other) const {
        return dist > other.dist;
    }
};

ll dijkstra(int s, vector<vll> & d, vector<vector<pair<int, ll>>>& adj) {
    //s-> source, d -> distance
    //p -> predecessor
    // adjancency list is stored like:
    // adj[u] == {v,w} ; there is an edge (u,v) of weight w
    int n = adj.size();
    d.assign(3, vector(n,LINF));
   // p.assign(n, -1);

    priority_queue<State, vector<State>, greater<State>> pq;
    
    d[0][s] = 0;
    pq.push({0, s, 0});
    
    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();
        
        if (curr.dist > d[curr.coupon][curr.node])  
            continue;
        
        for (auto edge : adj[curr.node]) {
            int to = edge.first;
            int len = edge.second;
            int discounted = len/2;

            if (d[curr.coupon][to] > curr.dist + len) {  
                d[curr.coupon][to] = curr.dist + len;
                pq.push({d[curr.coupon][to], to, curr.coupon});
            }
            if(curr.coupon < 2 && d[curr.coupon + 1][to] > curr.dist + discounted) {  
                d[curr.coupon+ 1][to] = curr.dist + discounted;
                pq.push({d[curr.coupon + 1][to], to, curr.coupon + 1});
            }
        }
    }
    return min(d[0][n-1],min(d[1][n-1], d[2][n-1]));
}

int main(){
    int n , m ;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> adj(n);
    
    vector<vll> d ;
   
    vector<vector<pair<int,ll>>> adj_reversed(n);
    vector<ll>  d_reversed(n) ;
    for(int i = 0 ; i < m ; i++){
        int a , b ;ll w;
        cin >> a >> b >> w ;
        adj[a-1].push_back(make_pair(b-1,w));
        
    }
    ll ans = dijkstra(0,d,adj);
    cout << ans << endl ;
}