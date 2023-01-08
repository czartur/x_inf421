#ifndef MST_H
#define MST_H

#include <iostream>
#include <vector>
using namespace std;

class UnionFind{
    private:
    vector<int> par, size;

    public:
    UnionFind(int n);

    int find(int a);

    void unite(int a, int b);

    bool isSame(int a, int b);
};

struct Edge{  
    int u; // first vertice
    int v; // second vertice
    int c; // weight
    
    Edge(int n_u, int n_v, int n_c);
   
    bool operator<(const Edge& edge) const;

    friend ostream& operator<<(ostream& os, const Edge& edge);
};

vector<Edge> build_MST(vector<Edge> &EdgeList, int n);
void build_MST(vector<pair<int,int>> *adjList, vector<Edge> &EdgeList, int n);

void print(vector<Edge> tree);

vector<vector<pair<int,int>>> to_adj_list(vector<Edge> &edge_list, int n);

#endif