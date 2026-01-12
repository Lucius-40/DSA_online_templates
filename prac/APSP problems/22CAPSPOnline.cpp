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
    int n , m, k;  // number of vertices
    cin >> n >> m>> k ;
    vector<vector<int>> dist(n, vector<int>(n, INF));

    for(int i = 0 ; i < n ; i++){
        dist[i][i]=0 ;
    }


    vi capacity(n,0);
    for(int i = 0 ; i < n ; i++){
        cin >> capacity[i];
    }
    //vector<vector<int>> parent(n, vector<int>(n, -1));

    // make graph
    for(int  i = 0 ; i < m ; i++){
        int a , b, c ;
        cin >> a >> b >> c ;
        a-- ; b-- ;
        if(capacity[a]==-1 or capacity[b]==-1)continue;
        dist[a][b]= dist[b][a]= c ;
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

    //queries
    int q ;
    cin >> q ;
    for(int i = 0 ; i < q ; i++){
        vi cap = capacity ;
        int source ;
        cin >> source ;
        source -- ;
        for(int j=0 ; j < k ; j++){
            int candidate = INF ;
            int selectedLab = -1;
            
            // Find the closest lab with available capacity
            for(int p = 0 ; p < n ; p++){
                if(cap[p] > 0 && dist[source][p] < candidate){
                    candidate = dist[source][p];
                    selectedLab = p;
                }
            }
            
            // Reduce capacity of selected lab
            if(selectedLab != -1){
                cap[selectedLab]--;
            } else {
                candidate = -1;
            }
            
            cout << candidate << " ";
        }
        cout << endl ;
    }
    
    
    
    return 0;
}

