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
const int INF = 1e9;
const ll LINF = 1e18;
bool flag = false ;
struct Edge {
    int a, b, cost;
};


vector<Edge> edges;



void bellmanFord(int n, int v, vector<int>& ans)
{
    
    vector<int> d(n, INF);
    d[v] = 0;
    vector<int> p(n, -1);
    
    int x = - 1;
    for (int i = 0; i < n; ++i) {
         x = -1 ;
        vector<int> d_prev = d ;
        for (Edge e : edges)
            if (d_prev[e.a] < INF)
                if (d[e.b] > d_prev[e.a] + e.cost) {
                    d[e.b] = max(-INF, d_prev[e.a] + e.cost);
                    p[e.b] = e.a;
                    x = 2 ;
                }
    }
    if(x==2){
        flag = true ;
    }
    //cout << flag << " " << x << endl ;
    ans = d ;

    
}



int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n , m , k , b , e ;
    cin >> n >> m >> k >> b >> e ;
    unordered_map<int, bool> isCapital, isBlocked;
    for(int i = 0 ; i < k ; i++){
        int x ; cin >> x ;
        isCapital[x-1] = true ;
    }    
    for(int i = 0 ; i < b ; i++){
        int x ; cin >> x ;
        isBlocked[x-1] = true ;
    }  
    vi dests ;
    for(int i = 0 ; i < e ; i++){
        int x ; cin >> x ;
        dests.pb(x-1);
    }    

    for(int i = 0 ; i < m ; i++){
        int a ,b ,cost ;
        cin >> a>> b >> cost ;
        if(isBlocked[a-1] or isBlocked[b-1]){
            continue;
        }
        Edge e ;
        e.a = a-1 ;
        e.b = b-1 ;
        e.cost = cost ;
        edges.pb(e);
    }
    vvi ans(k, vector(n,INF));
    int c = 0 ;
    for(auto p : isCapital){
        int source = p.F;
        vi d(n);
        bellmanFord(n, source, d);
        ans[c++]= d ;
    }
    if(flag) cout << "Abyss Detected\n";
    
    else {
        for(auto p : dests){
            int mini = INF ;
            for(auto v : ans){
                mini =min(mini, v[p]);
            }

            if(mini == INF) cout << "INF";
            else cout << mini ;
            cout << endl ;
        }
    }



}