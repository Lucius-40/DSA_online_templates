#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int u, v;
    ll w;
};

struct EffEdge {
    ll eff;
    int u, v;
    ll orig;
};

struct DSU {
    int n;
    vector<int> p, sz;
    vector<int> safe_count;
    DSU(int n=0): n(n), p(n), sz(n,1), safe_count(n,0) {
        for (int i=0;i<n;++i) p[i]=i;
    }
    void init(int n_) {
        n = n_;
        p.resize(n); sz.assign(n,1); safe_count.assign(n,0);
        for (int i=0;i<n;++i) p[i]=i;
    }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    // returns tuple (merged, old_safe_a, old_safe_b)
    tuple<bool,int,int> unite(int a, int b){
        a = find(a); b = find(b);
        if (a==b) return {false, 0, 0};
        if (sz[a] < sz[b]) swap(a,b);
        p[b] = a;
        sz[a] += sz[b];
        int olda = safe_count[a], oldb = safe_count[b];
        safe_count[a] += safe_count[b];
        return {true, olda, oldb};
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    ll P;
    if (!(cin >> N >> M >> P)) return 0;
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
        edges.push_back({u,v,w});
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
            safe_only.emplace_back(e.w, e.u, e.v);
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
        auto [merged, sra, srb] = dsuA.unite(u,v);
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
        ll effw = e.w + P * (ll)cntRisk;
        eff.push_back({effw, e.u, e.v, e.w});
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
        auto [merged, sra, srb] = dsuB.unite(ee.u, ee.v);
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
        auto [merged, sra, srb] = dsuC.unite(ee.u, ee.v);
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
