#include <iostream>
#include <vector>
#include <unordered_map>
#include "MST.h"

typedef long long ll;
const int L = 5e5+5;
const int N = 2e5+5;
const int M = 3e5+5;

struct Query{
    int u, v, ind;
};

int vis[N], par[N], noise[N];
vector<pair<int,int>> queryList[L];
vector<pair<int,int>> adjList[N];
vector<Query> lca_inv[N];

int find(int x){ // updates noise[y] and par[y] for y in [x, head of set) 
    if(x == par[x]) return x;
    int head = find(par[x]); 
    noise[x] = max(noise[x], noise[par[x]]);
    return par[x] = head;
}

void dfs_lca(int u, int parent, vector<int> &pmax){
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
    for(auto [v,i] : queryList[u]) if(vis[v]) // if v visited in post order traversal
    lca_inv[find(v)].push_back({u,v,i}); // 'move up' v to the head of its set
 
    for(Query q: lca_inv[u]){
        int x = q.u, y = q.v, i = q.ind;

        // 'move up' x to the head of its set (we already did it to y)
        find(x);

        // is y the lca ? 
        if(y == u) pmax[i] = noise[x];
        else pmax[i] = max(noise[x], noise[y]);
    }
} 

int main(){ 
    int n, m, l;
    cin >> n >> m;

    vector<Edge> edgeList;
    while(m--){
        int u, v, c;
        cin >> u >> v >> c;
        // adjList[u-1].push_back({v-1,c});
        // adjList[v-1].push_back({u-1,c});
        edgeList.push_back(Edge(u-1, v-1, c)); 
    }

    build_MST(adjList, edgeList, n);

    cin >> l;
    for(int i=0; i<l; i++){
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        // note that it captures the indice 'i' 
        queryList[u].push_back({v, i});
        queryList[v].push_back({u, i});
    }

    vector<int> path_max(l);
    dfs_lca(0, 0, path_max);

    // output solutions by index order
    for(auto ans : path_max) cout << ans << endl;
}