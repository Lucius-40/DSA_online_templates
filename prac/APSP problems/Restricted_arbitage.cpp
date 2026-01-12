// 2. The "Restricted Exchange" ArbitrageIn the SPOJ Arbitrage problem, you look for any cycle 
//where the product of rates $> 1.0$. Let’s add a constraint based on transaction limits.
//The Twist:Every time you exchange currency, you must pay a fixed "flat fee" in terms of "steps.
//" You are looking for an arbitrage opportunity, 
//but there is a regulatory limit: you cannot perform more than $M$ total exchanges in your cycle 
//(e.g., $M = 10$). Find the maximum profit possible starting from currency $S$
//and returning to $S$ in exactly or at most $M$ steps.Why it's harder: The standard Floyd-Warshall doesn't care about the number of edges.
// Here, the number of edges is the primary constraint.



#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void solve(int caseNum) {
    int n;
    cin >> n;
    if (n == 0) return;

    map<string, int> nameToId;
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        nameToId[name] = i;
    }

    int m_edges;
    cin >> m_edges;

    // dp[steps][from][to]
    // We only need the current and previous step to save space
    int M_LIMIT = 10; // Let's say max 10 transactions allowed
    vector<vector<vector<double>>> dp(M_LIMIT + 1, vector<vector<double>>(n, vector<double>(n, 0.0)));

    for (int i = 0; i < m_edges; i++) {
        string u, v;
        double rate;
        cin >> u >> rate >> v;
        dp[1][nameToId[u]][nameToId[v]] = rate;
    }

    bool found = false;
    int stepsTaken = 0;

    // Transition for exactly 's' steps
    for (int s = 2; s <= M_LIMIT; s++) {
        for (int k = 0; k < n; k++) {         // Intermediate
            for (int i = 0; i < n; i++) {     // Start
                for (int j = 0; j < n; j++) { // End
                    dp[s][i][j] = max(dp[s][i][j], dp[s-1][i][k] * dp[1][k][j]);
                }
            }
        }

        // Check for arbitrage in exactly 's' steps
        for (int i = 0; i < n; i++) {
            if (dp[s][i][i] > 1.0) {
                found = true;
                stepsTaken = s;
                break;
            }
        }
        if (found) break;
    }

    cout << "Case " << caseNum << ": ";
    if (found) cout << "Yes (within " << stepsTaken << " steps)" << endl;
    else cout << "No" << endl;
}

int main() {
    int n, count = 1;
    while (cin >> n && n != 0) {
        // ... (Logic to handle the 'n' provided by main)
    }
    return 0;
}