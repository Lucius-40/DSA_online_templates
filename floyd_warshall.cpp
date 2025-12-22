#include<bits/stdc++.h>
using namespace std ;

class Solution {
    int INF = 1e8 ;
public:
    int findTheCity(int n, vector<vector<int>>& edges, int thresh) {
        vector<vector<int>> adj_mat(n, vector(n,INF));
       
        for(int i = 0 ; i < edges.size();  i ++){
            adj_mat[edges[i][0]][edges[i][1]]= edges[i][2];
            adj_mat[edges[i][1]][edges[i][0]]= edges[i][2];
            if(i < n)adj_mat[i][i] = 0 ;
        }

        for(int i = 0 ; i < n ; i++){
            for(int j =0 ; j < n ;j++){
                for(int k = 0 ; k < n ; k++)
                    adj_mat[j][k] = min(adj_mat[j][k], adj_mat[j][i]+adj_mat[i][k]);
            }
        }
        int low = INT32_MAX;
        int node=-1;
        for(int i = 0 ; i < n ; i++){
            int count = 0  ;
            for(int j = 0 ; j < n ; j++){
                if(adj_mat[i][j] <= thresh)count ++ ;
            }
            if(count <= low){
                low = count ;
                node = i ;
            }
        }
       
        return node ;
        
    }
};
