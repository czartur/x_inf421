#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "MST.h"
using namespace std;

// compute max noise level (BFS approach)
int query(int u, int v, vector<vector<pair<int,int>>> &adj){
    vector<int> vis((int) adj.size());
    queue <pair<int,int>> q;
    q.push({u,0});

    while(!q.empty()){
        int u = q.front().first;
        int max_noise = q.front().second;
        q.pop();

        if(u == v) return max_noise;

        for(int i=0; i< (int) adj[u].size(); i++){
            int cur_u = adj[u][i].first;
            int cur_weight = adj[u][i].second;
            if(!vis[cur_u]) q.push({cur_u, max(max_noise, cur_weight)});
        }
    }

    return -1; // v unreachable from u
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

    cin >> l;

    while(l--){
        int u, v;
        cin >> u >> v;
        cout << query(u-1, v-1, adjList) << endl;
    }

}