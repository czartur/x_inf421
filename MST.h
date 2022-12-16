#ifndef MST_H
#define MST_H

#include <iostream>
#include <vector>
using namespace std;

struct Edge{  
    int u; // first vertice
    int v; // second vertice
    int c; // weight
    
    Edge(int n_u, int n_v, int n_c);
   
    bool operator<(const Edge& edge) const;

    friend ostream& operator<<(ostream& os, const Edge& edge);
};


vector<Edge> build_MST(vector<Edge> &EdgeList, int n);

void print(vector<Edge> tree);

vector<vector<pair<int,int>>> to_adj_list(vector<Edge> &edge_list, int n);

#endif