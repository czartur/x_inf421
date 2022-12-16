#include <iostream>
#include <algorithm>
#include <vector>
#include "UnionFind.h"
#include "MST.h"
using namespace std;

// Kruskal's algo for MST
// tested here : https://www.codechef.com/problems/DAY5P3


Edge::Edge(int n_u, int n_v, int n_c) : u{n_u}, v{n_v}, c{n_c} {};

bool Edge::operator<(const Edge& edge) const {
    return make_pair(c, make_pair(u, v)) < make_pair(edge.c, make_pair(edge.u, edge.v)); 
}

ostream&  operator<<(ostream&os, const Edge& edge){
    os << edge.u << " <--[" << edge.c << "]--> " << edge.v;
    return os;
}

vector<Edge> build_MST(vector<Edge> &EdgeList, int n){
    vector<Edge> tree;
    sort(EdgeList.begin(), EdgeList.end());
    UnionFind UF = UnionFind(n);

    for(auto edge : EdgeList){
        if(!UF.isSame(edge.u, edge.v)){
            UF.unite(edge.u, edge.v);
            tree.push_back(edge);
        }
    }

    return tree;
}

void print(vector<Edge> tree){
    for (auto edge : tree) cout << edge << endl;
}

vector<vector<pair<int,int>>> to_adj_list(vector<Edge> &edge_list, int n){
    vector<vector<pair<int,int>>> ans(n);
    for(auto edge : edge_list){
        ans[edge.u].push_back({edge.v, edge.c});
        ans[edge.v].push_back({edge.u, edge.c});
    }
    return ans;
}