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

vvi graph_vec ;
int n; // number of vertices

vi color;


int dfs_timer = 0;

void dfs(int v) {
   
    color[v] = 1;
    for (int u : graph_vec[v])
        if (color[u] == 0)
            dfs(u);
    color[v] = 2;
    
}