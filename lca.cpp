#include <iostream>
#include <vector>
#include <queue>
#include "MST.h"
using namespace std;

const int rt = 0; // root
const int M = 25; // number of sparse jumps

// compute levels
void dfs(int u, vector<int> &vis, vector<vector<pair<int,int>>> &adj, vector<vector<int>> &anc, vector<vector<int>> &noise, vector<int> &h){
    vis[u] = 1;
    for(auto p : adj[u]){
        int v = p.first;
        int w = p.second;

        if(!vis[v]){
            h[v] = h[u]+1;
            anc[0][v] = u;
            noise[0][v] = w;
            dfs(v, vis, adj, anc, noise, h);
        }
    }
}

// build sparse table
void build_sparseTable(vector<vector<int>> &anc, vector<vector<int>> &noise){
    anc[0][rt] = rt;
    int n = (int) anc[0].size();
    for(int j=1; j<M; j++){
        for(int i=0; i<n; i++){
            anc[j][i] = anc[j-1][anc[j-1][i]];
            noise[j][i] = max(noise[j-1][i], noise[j-1][anc[j-1][i]]);
        }
    }
}

// compute query 
int query(int u, int v, vector<vector<int>> &anc, vector<vector<int>> &noise, vector<int> &h){
    int ans = 0;

    if(h[u] < h[v]) swap(u, v);

    // remise à niveau

    for(int j=M; j>=0; j--) {
        if(h[anc[j][u]] >= h[v]) {
            ans = max(ans, noise[j][u]);
            u = anc[j][u];
        }
    }

    // lca from same level

    if(u == v) return ans;
    
    for(int j=M; j>=0; j--){
        if(anc[j][u] != anc[j][v]){
            ans = max(ans, noise[j][u]);
            ans = max(ans, noise[j][v]);
            u = anc[j][u];
            v = anc[j][v];
        }
    }
    
    return max(ans, max(noise[0][u], noise[0][v]));
}

int main(){
    int n, m, l;
    cin >> n >> m;
    vector<Edge> edgeList;
    while(m--){
        int u, v, c;
        cin >> u >> v >> c;
        edgeList.push_back(Edge(u-1, v-1, c)); 
    }

    edgeList = build_MST(edgeList, n);

    vector<vector<pair<int,int>>> adjList = to_adj_list(edgeList, n);
    vector<vector<int>> anc(M, vector<int>(n)), noise(M, vector<int>(n)); // [j][u] --> 2^j positions above u
    vector<int> h(n), vis(n);

    dfs(rt, vis, adjList, anc, noise, h);
    build_sparseTable(anc, noise);

    cin >> l;

    while(l--){
        int u, v;
        cin >> u >> v;
        cout << query(u-1, v-1, anc, noise, h) << endl;
    } 
} 