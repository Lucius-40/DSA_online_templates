#include<bits/stdc++.h>

using namespace std ;
int n, m ;

#define ll long long int 
#define pii pair<int,int>

int x[4]= {0,0,1,-1};
int y[4]= {1,-1,0,0};

bool bound_check(int u , int v){
    return (u >= 0 and u < n and v >= 0 and v < m); 
}




map<pii, int> marker , color;
int dfs_marker = 0;

void dfs(pii v,vector<vector<int>>&vv) {
    
    color[v] = 1;
    marker[v] = dfs_marker;
    for (int i = 0 ; i < 4 ;i++){
        pii u = make_pair(v.first +x[i], v.second + y[i] );
        if (color[u] == 0 and bound_check(u.first, u.second) and vv[u.first][u.second] ==0){
            dfs(u,vv);
            marker[u] = dfs_marker ;
        }
    }    
    color[v] = 2;
    
}

int main(){
    cin >> n >> m ;
    vector<vector<int>>v(n, vector(m,0));
    for(int i = 0 ; i < n ; i++){
        for( int j = 0 ; j < m ; j++){
            cin >> v[i][j];
            if(v[i][j] == 0){
                color[make_pair(i,j)]= 0 ;
            }
        }
    }

    for(int i = 0 ; i < n ; i++){
        for( int j = 0 ; j < m ; j++){
             if(v[i][j] == 0 and color[make_pair(i,j)]==0 ){
                dfs_marker ++ ;
                dfs(make_pair(i,j), v);
             }
        }
    }

    int mi = INT32_MIN ;
    for(auto & p : marker){
        mi = max(mi, p.second);
    }

    cout << mi << endl ;
    

}
