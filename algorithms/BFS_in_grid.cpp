#include<bits/stdc++.h>
using namespace std ;
#define ll long long int 
int n , m ;
const int INF = 1e9 ;
int x[4]={0,0,1,-1};
int y[4]={1,-1,0,0};



bool bound_check(int u , int v){
    return (u >= 0 and u <= n-1 and v >= 0 and v <= m-1 );
}

void bfs_fire(pair<int,int>& s, vector<vector<int>>&fire_map)
{
    vector<vector<int>> adj; // adjacency list representation
    int n;                   // number of nodes
                       // source vertex

    queue<pair<int,int>> q;
    map<pair<int,int> , bool> used ;
    map<pair<int,int> , int> d ;
    
    
    d[s]= 0 ;
    q.push(s);
    used[s] = true;
    
    while (!q.empty())
    {
        pair<int,int> v = q.front();
        q.pop();
        for (int i = 0 ; i < 4 ; i++)
        {
            pair<int,int> u = make_pair(v.first + x[i], v.second + y[i]);
            if (!used[u] and bound_check(u.first, u.second) and fire_map[u.first][u.second] != -1)
            {
                used[u] = true;
                q.push(u);
                d[u] = d[v] + 1;
                
            }
        }
    }
    for(auto& r : d){
        int x = r.first.first ;
        int y = r.first.second ;
        if(d[r.first] < fire_map[x][y])
            fire_map[x][y] = d[r.first] ;
    }
}

void bfs(pair<int,int>& s, vector<vector<int>>&fire_map)
{
    vector<vector<int>> adj; // adjacency list representation
    int n;                   // number of nodes
                       // source vertex

    queue<pair<int,int>> q;
    map<pair<int,int> , bool> used ;
    map<pair<int,int> , int> d ;
    
    
    d[s]= 0 ;
    q.push(s);
    used[s] = true;
    
    while (!q.empty())
    {
        pair<int,int> v = q.front();
        q.pop();
        for (int i = 0 ; i < 4 ; i++)
        {
            pair<int,int> u = make_pair(v.first + x[i], v.second + y[i]);
            if (!used[u] and bound_check(u.first, u.second) and d[v]+1 < fire_map[u.first][u.second] and fire_map[u.first][u.second] != -1)
            {
                used[u] = true;
                q.push(u);
                d[u] = d[v] + 1;
                
            }
        }
    }
    int ans = INT32_MAX ;
    for(auto& p : d){
        int x = p.first.first ;
        int y = p.first.second ;
        if(x == 0 or y==0 or x == n-1 or y == m-1 ){
            ans = min(ans, d[p.first]);
        }
    }
    if(ans != INT32_MAX){
        cout << "YES"<<endl ;
        cout << ans ;
    }
    else cout << "NO"<<endl ;
}


int main(){
    
    cin >> n >> m ;
    vector<pair<int,int>> fire_coords ;
    pair<int,int> source ;
    vector<vector<int>>v(n, vector(m,0));
    vector<vector<int>>fire_map(n, vector(m,INF));
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            cin >> v[i][j];
            if(v[i][j] == 2){
                fire_coords.push_back(make_pair(i,j));
            }
            if(v[i][j] == 1){
                fire_map[i][j] = -1 ;  
            }
            if(v[i][j] == 3){
                source = make_pair(i,j);
            }
            

        }
    }
    for(auto& p : fire_coords){
        bfs_fire(p, fire_map);
    }
    
    
    
    bfs(source, fire_map);
    


}