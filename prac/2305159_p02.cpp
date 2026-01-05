#include<bits/stdc++.h>
using namespace std ;
#define ll long long int
struct Edge {
    int a, b, cost;
};

int flag = false ;
vector<Edge> edges;
const ll INF = 1e18;


void bellmanFord(int n, int v)
{
    
    vector<ll> d(n, INF);
    d[v] = 0;
    vector<int> p(n, -1);
    int x;
    for (int i = 0; i < n; ++i) {
        x = -1;
        vector<ll> d_prev = d ;
        for (Edge e : edges)
            if (d_prev[e.a] < INF)
                if (d[e.b] > d_prev[e.a] + e.cost) {
                    d[e.b] = max(-INF, d_prev[e.a] + e.cost);
                    p[e.b] = e.a;
                    x = e.b;
                }
    }

    if (x == -1)
        return ;
    else {
        flag = true ;
        int y = x;
        for (int i = 0; i < n; ++i)
            y = p[y];

        vector<int> path;
        for (int cur = y;; cur = p[cur]) {
            path.push_back(cur);
            if (cur == y && path.size() > 1)
                break;
        }
        reverse(path.begin(), path.end());
        path.pop_back();

        cout << "Negative cycle: ";
        for (int u : path)
            cout << u+1 << " ";
        
    }
}

int main(){
    int n , m;
    cin >> n >> m ;
    for(int i = 0 ; i < m ; i++){
        Edge e;
        cin >> e.a >>e.b >> e.cost ;
        e.a -- ;
        e.b -- ;
        edges.push_back(e);
    }
    
    for(int i = 0 ; i <n ; i++){
        if(flag) break ;
        bellmanFord(n,i);
        // running n times so that unreachable negative cycles can be detected too
    }
    if(!flag){
        cout<< -1 <<endl ;
    }

}