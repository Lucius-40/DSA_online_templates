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

struct edge{
    int a ; int b; int c ;
};

// Function to reconstruct shortest path between two vertices
vector<int> getPath(int start, int end, vector<vector<int>>& parent) {
    if(parent[start][end] == -1) {
        return {};  // No path exists
    }
    
    vector<int> path;
    while(end != start) {
        path.push_back(end);
        end = parent[start][end];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int n , m;  // number of vertices
    cin >> n >> m ;
    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<edge> edges ;
    //vector<vector<int>> parent(n, vector<int>(n, -1));

    // make graph
    for(int  i = 0 ; i < m ; i++){
        int a , b, c ;
        cin >> a >> b >> c ;
        //a-- ; b-- ;
        dist[a][b]=c ;
        edge e ;
        e.a = a ;
        e.b = b ;
        e.c= c ;
        edges.pb(e);
    }


    // int x,y ;
    // cin >> x>> y ;
    //x-- ; y-- ;
    // Initialize distance matrix

    for(int i = 0 ; i < n ; i++){
        dist[i][i]=0 ;
    }

    //floyd-warshall
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(dist[i][k] != INF && dist[k][j] != INF) {
                    if(dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        // parent[i][j] = parent[k][j];
                    }
                }
            }
        }
    }

    vvi dist_cupons = dist ;
    // cupon logic 
    for(auto e : edges){
        for(int i =0 ; i < n ;i++){
            for(int j = 0 ; j < n ; j++){
                int candidate = (dist[i][e.a] < INF and dist[e.b][j] < INF)?dist[i][e.a] + e.c/2 + dist[e.b][j]: INF;
                if(candidate < dist_cupons[i][j]){
                    dist_cupons[i][j] = candidate ;
                }
            }
        }
    }

    //queries
    int q ;
    cin >> q ;
    for(int i = 0 ; i < q ; i++){
        int source, dest ;
        cin >> source >> dest ;
        //source -- , dest -- ;
       
        cout << dist[source][dest]<<endl ;
    }
    
    
    
    return 0;
}

// #include <bits/stdc++.h>
// using namespace std;

// typedef long long ll;
// const ll LINF = 1e15; // Large but safe from overflow when added

// void solve() {
//     int n, m;
//     if (!(cin >> n >> m)) return;

//     // dist[0] = no coupon, dist[1] = one coupon used
//     vector<vector<ll>> d0(n, vector<ll>(n, LINF));
//     vector<vector<ll>> d1(n, vector<ll>(n, LINF));

//     for (int i = 0; i < n; i++) d0[i][i] = d1[i][i] = 0;

//     for (int i = 0; i < m; i++) {
//         int u, v;
//         ll w;
//         cin >> u >> v >> w;
//         // Basic Floyd-Warshall usually assumes 0-indexed or 1-indexed. 
//         // If your input is 0-indexed, keep u, v as is.
//         d0[u][v] = min(d0[u][v], w);
//         d1[u][v] = min(d1[u][v], w / 2); // Applying coupon to direct edge
//     }

//     // Floyd-Warshall O(N^3)
//     for (int k = 0; k < n; k++) {
//         for (int i = 0; i < n; i++) {
//             for (int j = 0; j < n; j++) {
//                 // Update standard APSP
//                 if (d0[i][k] + d0[k][j] < d0[i][j]) {
//                     d0[i][j] = d0[i][k] + d0[k][j];
//                 }
                
//                 // Update Discounted APSP
//                 // Choice 1: Use coupon on the path from i to k
//                 // Choice 2: Use coupon on the path from k to j
//                 ll choice1 = d1[i][k] + d0[k][j];
//                 ll choice2 = d0[i][k] + d1[k][j];
                
//                 d1[i][j] = min({d1[i][j], choice1, choice2});
//             }
//         }
//     }

//     int q;
//     cin >> q;
//     while (q--) {
//         int s, t;
//         cin >> s >> t;
//         ll ans = d1[s][t];
//         if (ans >= LINF) cout << -1 << endl;
//         else cout << ans << endl;
//     }
// }

// int main() {
//     ios::sync_with_stdio(0); cin.tie(0);
//     solve();
//     return 0;
// }