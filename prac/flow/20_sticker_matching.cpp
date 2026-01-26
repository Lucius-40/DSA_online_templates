#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cap, flow, rev;
};
vector<vector<Edge>> adj;

void add_edge(int u, int v, int c) {
    adj[u].push_back({v, c, 0, (int)adj[v].size()});
    adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
}

int bfs(int s, int t, vector<int>& parent_edge, vector<int>& parent_node) {
    fill(parent_node.begin(), parent_node.end(), -1);
    parent_node[s] = -2;
    queue<pair<int,int>> q;
    q.push({s, 1e9});
    while(!q.empty()) {
        int v = q.front().first;
        int flow = q.front().second;
        q.pop();
        for(int i=0;i<adj[v].size();i++) {
            Edge &e = adj[v][i];
            if(parent_node[e.to]==-1 && e.cap-e.flow>0) {
                parent_node[e.to]=v;
                parent_edge[e.to]=i;
                int new_flow=min(flow,e.cap-e.flow);
                if(e.to==t) return new_flow;
                q.push({e.to,new_flow});
            }
        }
    }
    return 0;
}

int maxflow(int s,int t,int n) {
    int flow=0,new_flow;
    vector<int> parent_edge(n),parent_node(n);
    while(new_flow=bfs(s,t,parent_edge,parent_node)) {
        flow+=new_flow;
        int cur=t;
        while(cur!=s) {
            int prev=parent_node[cur];
            int idx=parent_edge[cur];
            adj[prev][idx].flow+=new_flow;
            int rev_idx=adj[prev][idx].rev;
            adj[cur][rev_idx].flow-=new_flow;
            cur=prev;
        }
    }
    return flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin>>n>>m;
    int total_nodes = n+m+2;
    int source=0, sink=n+m+1;
    adj.assign(total_nodes, {});

    // read your stickers
    int my_count; cin>>my_count;
    vector<int> my_stickers(my_count);
    for(int i=0;i<my_count;i++) cin>>my_stickers[i];
    vector<int> my_freq(m+1,0);
    for(int s:my_stickers) my_freq[s]++;

    // Source -> Sticker
    for(int i=1;i<=m;i++) {
        if(my_freq[i]>0) add_edge(source,i,my_freq[i]);
    }

    // read friends
    vector<vector<int>> friend_freq(n, vector<int>(m+1,0));
    for(int j=0;j<n;j++) {
        int cnt; cin>>cnt;
        for(int k=0;k<cnt;k++) {
            int s; cin>>s;
            friend_freq[j][s]++;
        }
    }

    // Sticker -> Friend edges
    for(int i=1;i<=m;i++) {
        for(int j=0;j<n;j++) {
            if(friend_freq[j][i]==0) {
                add_edge(i, m+1+j, 1);
            }
        }
    }

    // Friend -> Sticker edges
    for(int j=0;j<n;j++) {
        for(int i=1;i<=m;i++) {
            if(friend_freq[j][i]>1) {
                add_edge(m+1+j, i, friend_freq[j][i]-1);
            }
        }
    }

    // Sticker -> Sink
    for(int i=1;i<=m;i++) {
        add_edge(i, sink, 1);
    }

    int result = maxflow(source,sink,total_nodes);
    cout<<result<<"\n";

    // Print exchanges
    for(int i=1;i<=m;i++) {
        for(auto &e:adj[i]) {
            if(e.to>=m+1 && e.to<=m+n && e.flow>0) {
                int friend_id = e.to-(m+1)+1;
                // find which sticker came back
                for(auto &back:adj[e.to]) {
                    if(back.flow>0 && back.to>=1 && back.to<=m) {
                        cout<<"Exchange sticker "<<i<<" with sticker "<<back.to
                            <<" of friend "<<friend_id<<"\n";
                    }
                }
            }
        }
    }
}