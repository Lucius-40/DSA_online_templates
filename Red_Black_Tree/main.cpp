#include <bits/stdc++.h>
#include "RB_tree.hpp"

using namespace std;

int main() {
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    Red_Black_Tree<int, int> tree;
    int n;
    cin >> n;

    cout << n << "\n";

    for (int i = 0; i < n; i++) {
        int ei, xi;
        cin >> ei >> xi;

        int ri = 0; 

        if (ei == 0) {
            
            ri = tree.delete_key(xi) ? 1 : 0;
        } 
        else if (ei == 1) {
            
            ri = tree.insert(xi, xi) ? 1 : 0;
        } 
        else if (ei == 2) {
            
            int dummy;
            ri = tree.search(xi, dummy) ? 1 : 0;
        } 
        else if (ei == 3) {
            
            ri = tree.countLess(xi);
        }

        cout << ei << " " << xi << " " << ri << "\n";
    }

    return 0;
}
