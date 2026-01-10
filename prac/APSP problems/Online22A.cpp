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


int main(){
    int n , m , k , x;
    cin >> n >> m >> k >> x ;

    vvi lords(2, vector(k,0));
    for(int i = 0 ; i < 2 ; i++){
        for(int j = 0 ; j < k ; j++){
            cin >> lords[i][j];
            if(i == 0){
                lords[i][j]-- ;
            }
        }
    }

    vvi dist(n, vector(n,INF));
    vvi parent(n, vector<int>(n, -1));

    for(int i = 0 ; i < n ; i++){
        dist[i][i] = 0 ;
    }

    for(int i = 0 ; i < m ; i++){
        int a , b,c ;
        cin >>a >>b >> c ;
        a-- ; b-- ;
        dist[a][b] = c ;
        dist[b][a] = c ;
        parent[a][b] = a ; 
        parent[b][a] = b ;
    }


    for(int z = 0; z < n; z++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(dist[i][z] != INF && dist[z][j] != INF) {
                    if(dist[i][j] > dist[i][z] + dist[z][j]) {
                        dist[i][j] = dist[i][z] + dist[z][j];
                        parent[i][j] = parent[z][j];
                    }
                }
            }
        }
    }

    vi reachable ;
    for(int city = 0 ; city < n ; city ++){
        bool flag = false ;
        for(int i = 0 ; i < k ; i++){
            int lordcity = lords[0][i];
            int time = dist[lordcity][city];
            if(time > x){flag = true ; break ;}
        }
        if(!flag)reachable.pb(city);
    }

    if(reachable.size() <= 0){
        cout << "Not possible";
    }
    else {
    int low = INT32_MAX ;
    int dest = -1 ;
    for(int i = 0 ; i < reachable.size(); i++){
        int s = 0 ;
        
        for(int j = 0 ; j < k ; j++){
            int city = lords[0][j];
            int opp = lords[1][j];
            int time = dist[city][reachable[i]];
            s += (time*opp) ; 
        }
        if(s < low){
            low = s ;
            dest = reachable[i];
        }
    }
    int t_max = INT32_MIN ;
    for(int i = 0 ; i < k ; i++){
        int time = dist[lords[0][i]][dest];
        t_max = max(time, t_max);
    }

    cout << dest+1 << " "<<low<<" "<< t_max<< endl  ;

    for(int i = 0 ; i < k ; i++){
        vi path = getPath(lords[0][i], dest, parent) ;
        for(int ip : path)cout << ip+1 << " ";
        cout << lords[1][i] * dist[lords[0][i]][dest];
        cout << endl ;
    }

}

    
}