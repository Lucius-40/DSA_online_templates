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

int kruskal(int n, vector<Edge>&edges, vector<Edge>& mstEdges){
    sort(edges.begin(), edges.end(), comp);

    DSU dsu(n);

    int cost = 1, count = 0; 

    for(Edge e: edges){
        int u, v, wt;

        u = e.u;
        v = e.v;
        wt = e.weight;

        if(dsu.find_set(u) != dsu.find_set(v)){

            dsu.union_set(u, v);
            cost *= wt;
            mstEdges.push_back(e);
            
            count++;
            if(count == n-1)
                break;
        }
    }

    if(count != n-1){
        return -1;
    }

    return cost;
}

// Build adjacency list of MST
vector<vector<pii>> buildMSTGraph(int n, vector<Edge>& mstEdges){
    vector<vector<pair<int,int>>> g(n);
    for(auto &e: mstEdges){
        g[e.u].push_back({e.v,e.weight});
        g[e.v].push_back({e.u,e.weight});
    }
    return g;
}


//find max edge weight on path u-v in mst
int maxEdgeOnPath(int n, vector<vector<pair<int, int>>>& adj, int u, int v){
    vector<int> parent(n, -1), maxW(n, 0);

    queue<int>q;
    q.push(u);

    parent[u] = u;

    while(!q.empty()){
        int cur = q.front();
        q.pop();

        if(cur == v)
            break;

        for(auto &p: adj[cur]){
            int next = p.first, w = p.second;

            if(parent[next] == -1){
                parent[next] = cur;
                maxW[next] = max(maxW[cur], w);
                q.push(next);
            }
        }
    }

    return maxW[v];
}


int secondBestMST(int n, vector<Edge>&edges){
    
    vector<Edge> mstEdges;
    int mstCost=kruskal(n,edges,mstEdges);
    if(mstCost==-1) return -1;

    auto adj = buildMSTGraph(n, mstEdges);

    // Put MST edges in a set for quick lookup
    set<pair<int,int>> mstSet;
    for(auto &e: mstEdges){
        mstSet.insert({min(e.u,e.v), max(e.u,e.v)});
    }

    ll secondBest = INF;

    for(Edge e: edges){
        pii key = {min(e.u, e.v), max(e.u, e.v)};

        if(mstSet.count(key))
            continue; //skip mst edges

        int maxW = maxEdgeOnPath(n, adj, e.u, e.v);

        if(maxW == 0)
            continue;

        ll newCost = (mstCost * e.weight )/ maxW;
        //je cycle ta created hoise, oitar maxW baaddiye new weight ta add

        if(newCost > mstCost && newCost < secondBest){
            secondBest = newCost;
        }
    }

    return secondBest == INF ? -1 : secondBest;
}

int main()
{
    freopen("input.txt","r", stdin);
    int n, m;

    cin >> n >> m;

    vector<Edge>edges;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;

        cin >> u >> v >> w;

        edges.pb({u-1, v-1, w});
    }

    cout << secondBestMST(n, edges) << endl;
}

