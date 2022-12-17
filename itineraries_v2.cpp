#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#include "MST.h"
using namespace std;

//Using HINT (exercice 3)

vector<vector<int>> g;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int n) {
    for (int l = 1; l < (int) log(n); l++)
        up[v][l] = up[up[v][l - 1]][l - 1];
    tin[v] = t++;
    for (int u : g[v]) {
        up[u][0] = v;
        dfs(u);
    }
    tout[v] = t;
}

bool upper (int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b, int n) 
{
	if (upper(a, b))  return a;
	if (upper(b, a))  return b;
	for (int i = (int) log(n); i >= 0; i--)
		if (!upper(up[a][i], b))
			a = up[a][i];
	return up[a][0];
}

int main()
{
  //pour le moment comme ça, encore à penser
    int n, m, l;
    cin >> n >> m;
    vector<Edge> edgeList;
    while(m--){
        int u, v, c;
        cin >> u >> v >> c;
        edgeList.push_back(Edge(u-1, v-1, c)); 
    }
}

