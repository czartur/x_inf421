#include <iostream>
#include <vector>
#include <algorithm>
#include "MST.h"
using namespace std;


const int N = 2e5+5;
const int K = 25;

int T;

vector<pair<int,int>> adjList[N];
int up[K+2][N]; // sparse table of ancestors 
int noise[K+2][N]; // sparse table of noises
int tin[N], tout[N]; // time_in, time_out

// preprocessing 
void dfs(int v, int par){ 
    tin[v] = T++;
    for (auto [u,w] : adjList[v]) {
        if (u == par) continue;
        up[0][u] = v;
        noise[0][u]= w;
        dfs(u, v);
    }
    tout[v] = T;
}

// fill sparse table accordingly :
// * up[j][i] = 2^j-th ancestor of i 
// * noise[j][i] = max noise between i and up[j][i]
void search_ancestor_and_maxnoise(int n){

    up[0][0] = 0; // parent's root (0) is itself 
    for(int j = 1; j < K; j++){
        for(int i = 0; i < n; i++){
            up[j][i] = up[j - 1][up[j - 1][i]];
            noise[j][i] = max(noise[j - 1][i], noise[j - 1][up[j - 1][i]]);
	    }
	}
}

//true if "a" is an ancestor of "b"
bool upper (int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

//calculate path max noise between u and v
int query(int v, int u) {
    int res = 0;
    if (v == u) return 0; // 

    for (int l = K; l >= 0; l--){
        if (!upper(up[l][v], u)){
            res = max(res, noise[l][v]);
            v = up[l][v];
        }
    }
    
    for (int l = K; l >= 0; l--){
        if (!upper(up[l][u], v)){
            res = max(res, noise[l][u]);
            u = up[l][u];
        }
    }
    if(upper(u,v)) return max(res, noise[0][v]);
    if(upper(v,u)) return max(res, noise[0][u]);
    return max({res, noise[0][u], noise[0][v]});
}

int main(){
    int n, m, l;
    cin >> n >> m;
    
    //enter our graph with all edges and noises on the all edges
    vector<Edge> edgeList;
    while(m--){
        int u, v, c;
        cin >> u >> v >> c;
        // adjList[u-1].push_back({v-1,c});
        // adjList[v-1].push_back({u-1,c});
        edgeList.push_back(Edge(u-1, v-1, c)); 
    }

	//make a minimum spanning tree
    build_MST(adjList, edgeList, n);
   
    dfs(0, 0);
    search_ancestor_and_maxnoise(n);

    cin >> l;
    while(l--){
      int u, v;
        cin >> u >> v;
        cout << query(u-1, v-1) << endl;
    }    
}

