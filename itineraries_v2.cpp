#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#include "MST.h"
using namespace std;
#define db(x) cerr << #x << " == " << x << endl

vector<int> tin, tout; //time_in, time_out
vector<vector<int>> up; // we keep the ancestors 2 ** i here
vector<int> visited;
int t = 0;
vector<vector<pair<int,int>>> adjList;
vector<vector<int>> noise; //the noise in our graph

//preprocessing
void dfs(int v)
{ 
    visited[v] = true;
    tin[v] = t++;
    for (auto u : adjList[v]) {
        if (visited[u.first]) continue;
        up[0][u.first] = v;
        noise[0][u.first]= u.second;
        dfs(u.first);
    }
    tout[v] = t;
}

//search the 2^i-th upestor and the max noise between this ancestor and the initial vertex 
void search_ancestor_and_maxnoise(int n){

    up[0][0] = 0;
    for(int j = 1; j < 25; j++){
        for(int i = 0; i < n; i++){
            up[j][i] = up[j - 1][up[j - 1][i]];
            noise[j][i] = max(noise[j - 1][i], noise[j - 1][up[j - 1][i]]);
	    }
	}
}

//watch if it is an ancestor or not
bool upper (int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

//search the maximum noise
//problem is here
int get_max(int v, int u, int n ) {
    int res = 0;
    if (v == u) return 0; // it is the same vertex

    for (int l = 25; l >= 0; l--){
        if (!upper(up[l][v], u)){
            res = max(res, noise[l][v]);
            v = up[l][v];
        }
    }
    for (int l = 25; l >= 0; l--){
        if (!upper(up[l][u], v)){
            res = max(res, noise[l][u]);
            u = up[l][u];
        }
    }
    if(upper(u,v)) return max(res, noise[0][v]);
    if(upper(v,u)) return max(res, noise[0][u]);
    return max({res, noise[0][u], noise[0][v]});
}

int main()
{
    int n, m, l;
    cin >> n >> m;
    vector<Edge> edgeList;
    //enter our graph with all edges and noises on the all edges
    while(m--){
        int u, v, c;
        cin >> u >> v >> c;
        edgeList.push_back(Edge(u-1, v-1, c)); 
    }
	//make a minimum spanning tree
    edgeList = build_MST(edgeList, n);
    adjList = to_adj_list(edgeList, n);
    
    //initialization of all the arrays
    up.resize(30, vector<int>(n));
    noise.resize(30, vector<int>(n));
    tin.resize(n);
    tout.resize(n);
    visited.resize(n);
    
    dfs(0);
    search_ancestor_and_maxnoise(n);
    cin >> l;

    while(l--){
      int u, v;
        cin >> u >> v;
        cout << get_max(u-1, v-1, n) << endl;
    }

    
}

