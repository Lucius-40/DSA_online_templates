#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define pii pair<int,int>
#define vi vector<int>
#define vll vector<ll>
#define pb push_back
#define all(x) x.begin(), x.end()
#define F first
#define S second

const ll INF = 1e15;


struct Edge {
    int u;
    int v;
    int weight;
};

class DSU {
private:
    vector<int> parent;
    vector<int> rank;
    int n;

public:
    // Constructor
    DSU(int size) : n(size) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find with path compression
    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    // Union by rank
    void union_set(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }

    // Reset the DSU
    void reset() {
        rank.assign(n, 0);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
};



bool comp(Edge a, Edge b){
   return a.weight < b.weight;
}