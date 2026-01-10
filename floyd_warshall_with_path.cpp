#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// Function to reconstruct shortest path between two vertices
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

int main() {
    int n = 4;  // number of vertices
    
    // Initialize distance matrix
    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<vector<int>> parent(n, vector<int>(n, -1));

    

    

    
    // Floyd-Warshall algorithm with parent tracking
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(dist[i][k] != INF && dist[k][j] != INF) {
                    if(dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        parent[i][j] = parent[k][j];
                    }
                }
            }
        }
    }
    
    
    
    return 0;
}

