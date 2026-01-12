#include<bits/stdc++.h>
using namespace std ;
#define ll long long int
const ll INF = 1e18 ;

int main(){
    int n , m , q;
    cin >> n >> m >> q ;
    vector<vector<ll>> adj_matrix(n, vector(n, INF));
    for(int i = 0 ; i < m ; i++){
        int x , y, z ;
        cin >> x >> y >>  z ;
        adj_matrix[x-1][y-1]= z ;
        adj_matrix[y-1][x-1] = z ;
    }
    for(int i = 0 ; i < n ; i++){
        adj_matrix[i][i] = 0 ;
    }

    for(int via = 0 ; via < n ; via ++){
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                adj_matrix[i][j]= min(adj_matrix[i][j], adj_matrix[i][via] + adj_matrix[via][j]);
            }
        }
    }



    for(int i = 0 ; i < q ; i++){
        int a ,b ;
        cin >> a >> b ;
        if(adj_matrix[a-1][b-1] == INF){
            cout << -1 << endl ;
        }
        else cout << adj_matrix[a-1][b-1] << endl ;
    }
}
