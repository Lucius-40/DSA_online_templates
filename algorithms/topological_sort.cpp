#include <bits/stdc++.h>

using namespace std;
bool flag = true;

void dfs(char v, unordered_map<char, vector<char>> &adj, map<char, bool> &visited, vector<char> &ans, set<char> &s, map<char, int> &color)
{

    visited[v] = true;
    color[v] = 1;

    for (char u : adj[v])
    {
        if (color[u] == 1)
        {
            flag = false;
        }
        if (!visited[u])
            dfs(u, adj, visited, ans, s, color);
    }
    color[v] = 2;
    if (s.find(v) == s.end())
    {
        ans.push_back(v);
        s.insert(v);
    }
}

void solve()
{
    int n;
    cin >> n;
    vector<string> input;
    unordered_map<char, vector<char>> adj;
    vector<char> ans;
    map<char, int> color; // 0 white 1 gray 2black
    set<char> s;
    map<char, bool> visited;
    int max = INT32_MIN;
    for (int i = 0; i < n; i++)
    {
        string x;
        cin >> x;
        int l = x.size();
        if (l > max)
            max = l;
        input.push_back(x);
    }

    for (int i = 0; i < n; i++)
    {
        char prev = input[i][0];
        for (int j = 0; j <input[i].size(); j++)
        {
            if (prev != input[i][j])
                adj[prev].push_back(input[i][j]);
            prev = input[i][j];
        }
    }
   
    for (auto &p : adj)
    {
        cout << p.first << ": ";
        for (char c : p.second)
            cout << c << " ";
        cout << endl;
    }

    for (auto &p : adj)
    {
        if (color[p.first] == 0)
            dfs(p.first, adj, visited, ans, s, color);
    }
    if (flag)
    {
        for (int i = ans.size() - 1; i >= 0; i--)
        {
            cout << ans[i];
        }
    }
    else{
        cout << -1 << endl ;
        flag = true ;
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}