#include <iostream>
#include <algorithm>
#include <vector>
#include "MST.h"
using namespace std;


// class Union Find

UnionFind::UnionFind(int n){
    size.assign(n,0);
    for(int i=0; i<n; i++) par.push_back(i);
}

int UnionFind::find(int a) { return par[a] == a ? a : par[a] = find(par[a]); }

void UnionFind::unite(int a, int b){

    // compare set representatives
    if((a = find(a)) == (b = find(b))) return; 

    // link smallest to largest
    if(size[a] < size[b]) swap(a,b); // a >= b always
    par[b] = a;
    size[a] += size[b]; 
}

bool UnionFind::isSame(int a, int b) { return find(a) == find(b); }


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

void build_MST(vector<pair<int,int>> *adjList, vector<Edge> &EdgeList, int n){
    vector<Edge> MStree;
    sort(EdgeList.begin(), EdgeList.end());
     
    UnionFind UF = UnionFind(n);

    // kruskal algorithm 
    for(auto edge : EdgeList){
        if(!UF.isSame(edge.u, edge.v)){
            UF.unite(edge.u, edge.v);
            MStree.push_back(edge);
        }
    }

    // to adjacency list
    for(auto edge : MStree){
        adjList[edge.u].push_back({edge.v, edge.c});
        adjList[edge.v].push_back({edge.u, edge.c});
    }
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