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

bool comp(vi a , vi b){
    return a[0] > b[0] ;
}

int main(){
    
    int n , m , k ;
    cin >> n >> m >> k ;
    
    // Check if n is too large for memory
    if(n > 1000) {
        cout << "Input too large for available memory" << endl;
        return 1;
    }
    
    vector<vll> dist(n, vll(n, INF));
    
    for(int i = 0 ; i < n ; i++){
        dist[i][i] = 0 ;
    }

    vvi source_dest(2, vi(n, INF));
    for(int i = 0 ; i < 2 ; i++){
        for(int j = 0 ; j < n ; j++){
            cin >> source_dest[i][j];
            source_dest[i][j]-- ;
        }
    }

    for(int i = 0 ; i < m ; i++){
        int a , b, c ;
        cin >> a >> b >> c ;a-- ;b-- ;
        dist[a][b] = c ;

    }


    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(dist[i][k] != INF && dist[k][j] != INF) {
                    if(dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        //parent[i][j] = parent[k][j];
                    }
                }
            }
        }
    }

   vector<vll> cost_source_dst;

   for(int i = 0 ; i < n ; i++){
        int s = source_dest[0][i];
        int d = source_dest[1][i];
        ll c = dist[s][d];
        if (c == INF)continue;
        cost_source_dst.pb({c,s,d});
   }

   sort(cost_source_dst.begin(), cost_source_dst.end(), comp);
   ll total = 0 ;
   for(int i = 0 ; i < cost_source_dst.size(); i++){
        int batch = i/ k ;
        ll factor = 1LL << batch;  // Use bit shift instead of pow for efficiency
        ll cost = (ll)cost_source_dst[i][0] * factor;
        total += cost ;
   }

    cout << total ;






}