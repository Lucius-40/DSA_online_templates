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



class Solution {
    #define pii pair<int,int>
    #define inf 1e8
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {

        vector<int>dist(n, inf);
        dist[src] = 0;

        

        

        for(int i = 0; i<=k; i++){
            int x = -1;
            vector<int>temp = dist;
            
            for(auto it: flights){
                int u = it[0];
                int v = it[1];
                int wt = it[2];

                if(temp[u] != inf && temp[u] + wt < dist[v]){
                    dist[v] = temp[u] + wt;
                    x = 2;
                }
            }

            if(x==-1)
                break;
            
        }

        return dist[dst] == inf ? -1 : dist[dst];
    }
};