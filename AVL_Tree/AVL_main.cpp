#include "AVL_tree.hpp"

using namespace std;

int main() {
    freopen("input.txt", "r",stdin);
    freopen("output.txt","w",stdout);
    AVL_Tree<int, int> tree;
    int n;
    cin >> n;
    
    cout << n << endl; 
    
    for (int i = 0; i < n; i++) {
        int ei, xi;
        cin >> ei >> xi;
        
        if (ei == 1) {
            bool ri = tree.insert(xi, xi) ? true : false;
            cout << ei << " " << xi << " " << ri << endl;
        }
        else if (ei == 0) {
            bool ri = tree.deleteKey(xi) ? true : false;
            cout << ei << " " << xi << " " << ri << endl;
        }
        else if (ei == 2) {
            tree.traversal(xi);
            cout << endl;
        }
        // cout << "\n debugging ";
        
        // tree.printTreeStructure();
        // cout << endl ;
    }
    // cout << endl ;
    // tree.printTreeStructure();
    
    return 0;
}