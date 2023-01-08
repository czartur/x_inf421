#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "MST.h"
using namespace std;

const int N = 2e5+5;
const int M = 3e5+5;
const int L = 5e5+5;

int n, m, l; 
vector<pair<int,int>> adjList[N];

// compute max noise level (BFS approach)
int query(int u, int v){
    vector<int> vis(n);
    queue <pair<int,int>> q;
    q.push({u,0});

    while(!q.empty()){
        int u = q.front().first;
        int max_noise = q.front().second;
        q.pop();
        
        if(u == v) return max_noise;

        for(int i=0; i< (int) adjList[u].size(); i++){
            int cur_u = adjList[u][i].first;
            int cur_weight = adjList[u][i].second;
            if(!vis[cur_u]) q.push({cur_u, max(max_noise, cur_weight)});
        }
    }

    return -1; // v unreachable from u
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
    
    //edgeList = build_MST(edgeList, n);
    //vector<vector<pair<int,int>>> adjList = to_adj_list(edgeList, n);
    
    cin >> l;
    while(l--){
        int u, v;
        cin >> u >> v;
        cout << query(u-1, v-1) << endl;
    }

}