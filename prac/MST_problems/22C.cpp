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
    ll weight;
};

struct EffEdge {
    ll eff;
    int u, v;
    ll orig;
};

class DSU {
private:
    vector<int> parent;
    vector<int> rank;
    int n;

public:
    vector<int> safe_count;
    
    // Constructor
    DSU(int size) : n(size) {
        parent.resize(n);
        rank.resize(n, 0);
        safe_count.resize(n, 0);
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

    // Union by rank with safe_count tracking
    // returns tuple (merged, old_safe_a, old_safe_b)
    tuple<bool, int, int> union_set(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a == b) return {false, 0, 0};
        
        int olda = safe_count[a], oldb = safe_count[b];
        
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
        
        safe_count[a] += safe_count[b];
        return {true, olda, oldb};
    }

    // Reset the DSU
    void reset() {
        rank.assign(n, 0);
        safe_count.assign(n, 0);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    ll P;
    cin >> N >> M >> P;
    int K; cin >> K;
    vector<char> risky(N, 0);
    for (int i=0;i<K;++i){
        int r; cin >> r;
        risky[r] = 1;
    }
    vector<Edge> edges;
    edges.reserve(M);
    for (int i=0;i<M;++i){
        int u,v; ll w; cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    // Count safe nodes
    vector<int> safe_nodes;
    for (int i=0;i<N;++i) if (!risky[i]) safe_nodes.push_back(i);
    if (safe_nodes.empty()){
        // No safe cities: trivial
        cout << 0 << "\n" << 0 << "\n";
        return 0;
    }
    int safe_components_init = (int)safe_nodes.size();

    // Phase A: safe-only edges
    vector<tuple<ll,int,int>> safe_only;
    for (auto &e: edges){
        if (!risky[e.u] && !risky[e.v]){
            safe_only.emplace_back(e.weight, e.u, e.v);
        }
    }
    sort(safe_only.begin(), safe_only.end(), [](auto &a, auto &b){
        return get<0>(a) < get<0>(b);
    });

    DSU dsuA(N);
    for (int i=0;i<N;++i) dsuA.safe_count[i] = (!risky[i]) ? 1 : 0;
    int safe_comp = safe_components_init;
    vector<pair<int,int>> chosenA;
    ll totalA = 0;
    for (auto &t: safe_only){
        ll w; int u,v; tie(w,u,v) = t;
        auto [merged, sra, srb] = dsuA.union_set(u,v);
        if (!merged) continue;
        // both endpoints safe => sra>0 or srb>0, and merging two safe components reduces safe_comp if both had safe nodes
        if (sra>0 && srb>0) safe_comp--;
        chosenA.emplace_back(u,v);
        totalA += w;
        if (safe_comp == 1) break;
    }
    if (safe_comp == 1){
        cout << chosenA.size() << "\n";
        for (auto &p: chosenA) cout << p.first << " " << p.second << "\n";
        cout << totalA << "\n";
        return 0;
    }

    // Phase B: full graph with effective weights
    vector<EffEdge> eff;
    eff.reserve(M);
    for (auto &e: edges){
        int cntRisk = (risky[e.u]?1:0) + (risky[e.v]?1:0);
        ll effw = e.weight + P * (ll)cntRisk;
        eff.push_back({effw, e.u, e.v, e.weight});
    }
    sort(eff.begin(), eff.end(), [](const EffEdge &a, const EffEdge &b){
        if (a.eff != b.eff) return a.eff < b.eff;
        if (a.u != b.u) return a.u < b.u;
        return a.v < b.v;
    });

    DSU dsuB(N);
    for (int i=0;i<N;++i) dsuB.safe_count[i] = (!risky[i]) ? 1 : 0;
    int safe_compB = safe_components_init;
    vector<EffEdge> chosen_all; chosen_all.reserve(N-1);
    ll total_all = 0;
    for (auto &ee: eff){
        auto [merged, sra, srb] = dsuB.union_set(ee.u, ee.v);
        if (!merged) continue;
        if (sra>0 && srb>0) safe_compB--;
        chosen_all.push_back(ee);
        total_all += ee.eff;
        if (safe_compB == 1) break;
    }
    if (safe_compB != 1){
        cout << -1 << "\n";
        return 0;
    }

    // Prune chosen_all to minimal subset that still connects all safe nodes.
    // Run Kruskal again but only on chosen_all edges (they are <= N-1), stop when safe nodes connected.
    sort(chosen_all.begin(), chosen_all.end(), [](const EffEdge &a, const EffEdge &b){
        if (a.eff != b.eff) return a.eff < b.eff;
        if (a.u != b.u) return a.u < b.u;
        return a.v < b.v;
    });
    DSU dsuC(N);
    for (int i=0;i<N;++i) dsuC.safe_count[i] = (!risky[i]) ? 1 : 0;
    int safe_compC = safe_components_init;
    vector<pair<int,int>> final_edges;
    ll final_total = 0;
    for (auto &ee: chosen_all){
        auto [merged, sra, srb] = dsuC.union_set(ee.u, ee.v);
        if (!merged) continue;
        if (sra>0 && srb>0) safe_compC--;
        final_edges.emplace_back(ee.u, ee.v);
        final_total += ee.eff;
        if (safe_compC == 1) break;
    }

    // Output final result
    cout << final_edges.size() << "\n";
    for (auto &p: final_edges) cout << p.first << " " << p.second << "\n";
    cout << final_total << "\n";
    return 0;
}