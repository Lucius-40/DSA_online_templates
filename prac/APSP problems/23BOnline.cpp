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
    int n , m;  // number of vertices
    cin >> n >> m ;
    vector<vector<int>> dist(n, vector<int>(n, INF));
    //vector<vector<int>> parent(n, vector<int>(n, -1));

    // make graph
    for(int  i = 0 ; i < m ; i++){
        int a , b, c ;
        cin >> a >> b >> c ;
        //a-- ; b-- ;
        dist[a][b]=c ;
    }


    int x,y ;
    cin >> x>> y ;
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

    //queries
    int q ;
    cin >> q ;
    for(int i = 0 ; i < q ; i++){
        int source, dest ;
        cin >> source >> dest ;
        //source -- , dest -- ;
        int candidate1 = dist[source][x]+  dist[x][dest];
        int candidate2 = dist[source][y]+ dist[y][dest];
        cout << min(candidate1, candidate2)<<endl ;
    }
    
    
    
    return 0;
}

