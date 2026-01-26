#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cap, flow, rev;
};

vector<vector<Edge>> adj;

struct peaky {
    int exp ;
    int age ;
    int cr ;
    int birm ;
    int weapon ;
    int trust_level ;
    int lang ;
};

struct other{
    int exp ;
    int age ;
    int cr ;
    int birm ;
    int weapon ;
    int trust_level ;
    int lang ;
};
bool isCompatible(peaky A , other B){
    if(abs(A.age - B.age) <= 5 and abs(A.exp - B.exp)<=12 and (A.cr == B.cr) and (A.birm == B.birm) and (A.weapon+ B.weapon >=1) and (A.trust_level+ B.trust_level >=10 )){
        if((A.lang & B.lang) == 0) return false;
        else return true ;
    }
    else return false ;
};


void add_edge(int from, int to, int cap) {
    Edge forward = {to, cap, 0, (int)adj[to].size()};
    Edge backward = {from, 0, 0, (int)adj[from].size()};
    adj[from].push_back(forward);
    adj[to].push_back(backward);
}


bool bfs(int s, int t, vector<int>& parent_edge, vector<int>& parent_node) {
    fill(parent_node.begin(), parent_node.end(), -1);
    parent_node[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, 1e9});

    while (!q.empty()) {
        int v = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int i = 0; i < adj[v].size(); i++) {
            Edge &e = adj[v][i];
            if (parent_node[e.to] == -1 && e.cap - e.flow > 0) {
                parent_node[e.to] = v;
                parent_edge[e.to] = i;
                int new_flow = min(flow, e.cap - e.flow);
                if (e.to == t) return new_flow;
                q.push({e.to, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(int s, int t, int n) {
    int flow = 0;
    vector<int> parent_edge(n);
    vector<int> parent_node(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent_edge, parent_node)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent_node[cur];
            int idx = parent_edge[cur];
            adj[prev][idx].flow += new_flow;
            int rev_idx = adj[prev][idx].rev;
            adj[cur][rev_idx].flow -= new_flow;
            cur = prev;
        }
    }
    return flow;
}

void solve(){
    int  n , m ;
    cin >> n >> m ;
    adj.clear();
    adj.assign(n+m+2, vector<Edge>());
    vector<peaky>blinders(n);
    vector<other> gang(m);
    for(int i = 0 ; i < n ; i++){
        
        cin >> blinders[i].exp >> blinders[i].age >> blinders[i].cr >> blinders[i].birm >> blinders[i].weapon >> blinders[i].trust_level>>blinders[i].lang;
    }
    for(int i = 0 ; i < m ; i++){
        cin >> gang[i].exp >> gang[i].age >> gang[i].cr >> gang[i].birm >> gang[i].weapon >> gang[i].trust_level>>gang[i].lang;
    
    }

    for(int i = 1 ; i <= n ;i++){
        add_edge(0,i,1);
    }
    for(int i = n+1 ; i <= (n+m) ; i++){
        add_edge(i, n+m+1,1);
    }

    for(int i = 1 ; i <=n ; i++ ){
        for(int j = n+1 ;  j <=(n+m) ; j++){
            if(isCompatible(blinders[i-1], gang[j-n-1])){
                add_edge(i,j,1);
            }
        }
    }

    cout << maxflow(0,n+m+1 ,n+m+2) << "\n";
}

int main() {
    freopen("input.txt","r",stdin);
    int t ;
    cin >> t ;
    while(t--){
        solve();
    }
    
}