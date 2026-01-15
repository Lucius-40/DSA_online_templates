#pragma once
#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define pii pair<int,int>
#define vi vector<int>
#define vll vector<ll>
#define pb push_back
#define all(x) x.begin(), x.end()
#define F first
#define S second

namespace DSU{

    struct Edge {
        int u;
        int v;
        int weight;
    };

    vi set, rank;

    void make_set(int v){
        set[v]=v ;
        rank[v]= 0 ;
    }
    int find_set(int v) {
        if (v == set[v])
            return v;
        return set[v] = find_set(set[v]);
    }

    void union_set(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            set[b] = a;
            if (rank[a] == rank[b])
            rank[a]++;
        }
    }

    void init(int n){
        set.resize(n);
        rank.resize(n);
        for(int i= 0 ; i < n ; i++)
            make_set(i);
    }
}