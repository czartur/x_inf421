#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int rt = 0; // root
const int M = 25; // number of sparse jumps
const int N = 1e5+1; // number of nodes

vector<vector<pair<int,int>>> adj;
vector<vector<int>> anc, noise; // [j][u] --> 2^j positions above u
vector<int> h, vis;

// compute levels
void dfs(int u){
    vis[u] = 1;
    for(auto p : adj[u]){
        int v = p.first;
        int w = p.second;

        if(!vis[v]){
            h[v] = h[u]+1;
            anc[0][v] = u;
            noise[0][v] = w;
            dfs(v);
        }
    }
}

// build sparse table
void build_sparseTable(){
    anc[0][rt] = rt; 
    for(int j=1; j<=M; j--){
        for(int i=0; i<N; i++){
            anc[j][i] = anc[j-1][anc[j-1][i]];
            noise[j][i] = max(noise[j-1][i], noise[j-1][anc[j-1][i]]);
        }
    }
}

// compute query 
int query(int u, int v){
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
    
    return ans;
}

int main(){

} 