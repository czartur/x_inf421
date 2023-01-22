#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#include "MST.h"
using namespace std;


vector<int> tin, tout; //time_in, time_out
vector<vector<int>> up; // we keep the ancestors 2 ** i here
vector<int> visited;
int t = 0;
vector<vector<pair<int,int>>> adjList;
vector<vector<int>> noise; //the noise in our graph

//preprocessing
void dfs(int v, int n)
{ 
    visited[v] = true;
<<<<<<< HEAD
    tin[v] = t++;    
=======
    tin[v] = t++;
>>>>>>> e78b16846c359a835c0efcb323f8a77ec5b05cb3
    for (auto u : adjList[v]) {
	if (!visited[u.first])
	{
           up[u.first][0] = v;
<<<<<<< HEAD
           noise[0][u.first] = u.second;
           noise[u.first][0] = u.second;
=======
           noise[v][u.first] = u.second;
           noise[u.first][v] = u.second;
>>>>>>> e78b16846c359a835c0efcb323f8a77ec5b05cb3
           dfs(u.first,n);
	}
    }
    tout[v] = t;
}

//search the 2^i-th upestor and the max noise between this ancestor and the initial vertex 
void search_ancestor_and_maxnoise(vector<vector<int>> &up, vector<vector<int>> &noise, int n){
<<<<<<< HEAD

    up[0][0] = 0;
    for(int j = 1; j < (int) log(n) - 1; j++){
        for(int i = 0; i < n; i++){
            up[i][j] = up[i - 1][up[i - 1][j]];
            noise[i][j] = max(noise[i - 1][j], noise[i - 1][up[i - 1][j]]);
=======
    up[0][0] = 0;
    int n = (int) uo[0].size();
    for(int j = 1; j < (int) log(n) - 1; j++){
        for(int i = 0; i < n; i++){
            up[j][i] = up[j - 1][up[j - 1][i]];
            noise[j][i] = max(noise[j - 1][i], noise[j - 1][up[j - 1][i]]);
>>>>>>> e78b16846c359a835c0efcb323f8a77ec5b05cb3
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
    for (int l = (int) log(n) - 1 ;l >= 0; l--)
    {
        if (!upper(up[v][l], u))
        {
            v = up[v][l];
            res = max(res, noise[v][l]);
        }
    }
    for (int l = (int) log(n) - 1; l >= 0; l--)
     {
        if (!upper(up[u][l], v))
        {
            u = up[u][l];
            res = max(res, noise[u][l]);
        }
     }
    return max({res, noise[v][0], noise[u][0]});
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
    up.resize(n, vector<int>((int)log(n) + 1));
    noise.resize(n, vector<int>(n));
    tin.resize(n);
    tout.resize(n);
    visited.resize(n);
    
    dfs(0, n);
    search_ancestor_and_maxnoise(up, noise, n);
    cin >> l;

    while(l--){
      int u, v;
        cin >> u >> v;
        cout << get_max(u-1, v-1, n) << endl;
<<<<<<< HEAD
=======
    }
    for (int i = 0; i < n; i++)
    {
    	for (int j = 0; j < n; j++)
    	{
   		cout << noise[i][j] << " ";
    	}
    	cout << '\n';
>>>>>>> e78b16846c359a835c0efcb323f8a77ec5b05cb3
    }
    
}

