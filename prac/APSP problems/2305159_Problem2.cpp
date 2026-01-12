#include <bits/stdc++.h>
using namespace std;
#define ll long long int
const double INF = 1e8;

int main()
{
    int n, m;
    cin >> n;
    vector<vector<double>> adj_matrix(n, vector(n, -INF));
    map<string, int> nodes;
    for (int i = 0; i < n; i++)
    {
        adj_matrix[i][i] = 1;
    }
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        nodes[s] = i;
    }
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        string x, y;
        double z;
        cin >> x >> z >> y;
        adj_matrix[nodes[x]][nodes[y]] = z;
        // adj_matrix[nodes[y]][nodes[x]] = z ;
    }

    for (int via = 0; via < n; via++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                adj_matrix[i][j] = max(adj_matrix[i][j], adj_matrix[i][via] * adj_matrix[via][j]);
            }
        }
    }

    bool flag = false;
    for (int i = 0; i < n; i++)
    {
        if (adj_matrix[i][i] > 1 and !flag)
        {
            cout << "Yes\n";
            flag = true;
        }
    }

    if (!flag)
        cout << "No\n";
}
