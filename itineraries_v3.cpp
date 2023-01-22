#include <iostream>
#include <vector>
#include <unordered_map>
#include "MST.h"

typedef long long ll;
const int L = 5e5+5;
const int N = 2e5+5;
const int M = 3e5+5;

int n, m, l;
int vis[N], par[N], noise[N];
vector<int> queryList[L];
vector<pair<int,int>> adjList[N], lca_inv[N];
//unordered_map<int, vector<pair<int,int>>> S;


inline ll key(int a, int b){
    return (ll)a*(ll)n + (ll)b;
}

pair<int,int> find(int x, int cur_noise){
    if(par[x] == x) return {x,0};

    pair<int,int> prox = find(par[x], noise[x]);

    return {par[x] = prox.first, noise[x] = max(noise[x], prox.second)};
}

void dfs_lca(int u, int parent, unordered_map<ll, int> &pmax){
    par[u] = u; // make a set containing u

    // accessing children of u 
    for(auto [v,w] : adjList[u]){ 
        if(v == parent) continue;  
        dfs_lca(v, u, pmax); 
        noise[v] = w; // max noise from v to the represent of its set (initialy the edge to its parent)
        par[v] = u; // unite v set to u 
    }

    vis[u] = 1; // u was post order traversed

    // finding lca of possible (u,v) queries 
    for(int v : queryList[u]) if(vis[v]) // if v visited in post order traversal
    lca_inv[find(v,0).first].push_back({u,v}); // 'move up' v to the head of its set
 
    for(auto [x,y]: lca_inv[u]){
        // 'move up' x to the head of its set (we already did it to y)
        find(x,0);

        // is y the lca ? 
        if(y == u) pmax[key(x,y)] = pmax[key(y,x)] = noise[x];
        else pmax[key(x,y)] = pmax[key(y,x)] = max(noise[x], noise[y]);
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
        queryList[u].push_back(v);
        queryList[v].push_back(u);
    }

    unordered_map <ll, int> path_max;
    dfs_lca(0, 0, path_max);

    for(auto q : queries) cout << path_max[q] << endl;
}