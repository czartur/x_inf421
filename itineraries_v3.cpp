#include <iostream>
#include <vector>
#include <unordered_map>
#include "MST.h"

typedef long long ll;
const int L = 5e5+5;
const int N = 2e5+5;
const int M = 3e5+5;

int n, m, l;
int vis[N], par[N], len[N];
vector<int> qList[L];
vector<pair<int,int>> adjList[N];
unordered_map<int, vector<pair<int,int>>> S;


inline ll key(int a, int b){
    return (ll)a*(ll)n + (ll)b;
}

pair<int,int> find(int x, int cur_len){
    if(par[x] == x) return {x,0};

    pair<int,int> prox = find(par[x], len[x]);

    return {par[x] = prox.first, len[x] = max(len[x], prox.second)};
}

void dfs_lca(int u, int parent, unordered_map<ll, int> &pmax){
    vis[u] = 1;
    par[u] = u;

    for(int v : qList[u]) if(vis[v]) 
    S[find(v,0).first].push_back({u,v});

    for(auto [v,w] : adjList[u]){
        if(v == parent) continue; 
        dfs_lca(v, u, pmax);
        len[v] = w; 
        par[v] = u;
    }
    
    for(auto [x,y]: S[u]){
        find(x,0);

        if(y == u) pmax[key(x,y)] = pmax[key(y,x)] = len[x];
        else pmax[key(x,y)] = pmax[key(y,x)] = max(len[x], len[y]);  
    }
} 

int main(){ 
    vector<Edge> edgeList;

    cin >> n >> m;
    while(m--){
        int u, v, c;
        cin >> u >> v >> c;
        edgeList.push_back(Edge(u-1, v-1, c)); 
    }

    build_MST(adjList, edgeList, n);

    vector<ll> queries;
    cin >> l;
    while(l--){
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        queries.push_back(key(u,v));
        qList[u].push_back(v);
        qList[v].push_back(u);
    }

    unordered_map <ll, int> path_max;
    dfs_lca(0, 0, path_max);

    for(auto q : queries) cout << path_max[q] << endl;
}