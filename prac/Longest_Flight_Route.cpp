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




int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n , m ;
    cin >> n >> m ;
    vector<vector<pii>> adj(n) ;
    for(int i = 0 ; i < m ; i++){
        int a , b ;
        cin >> a >> b ;
        adj[a-1].pb({b-1, -1});     
    }
    vi d(n), p(n);
    
}