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

    // start at u with zero max_noise 
    q.push({u,0});

    while(!q.empty()){
        int cur = q.front().first;
        int max_noise = q.front().second;
        q.pop();

        // test if v was reached
        if(cur == v) return max_noise;

        // iterate through childs of cur vertex
        for(int i=0; i < (int) adjList[cur].size(); i++){
            int child = adjList[u][i].first;
            int noise = adjList[u][i].second;
            
            // if child not visited, add to queue and update maximum noise seen 
            if(!vis[child]) q.push({child, max(max_noise, noise)});
        }
    }

    return -1; // v unreachable from u (expected to never happen)
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
    
    cin >> l;
    while(l--){
        int u, v;
        cin >> u >> v;
        cout << query(u-1, v-1) << endl;
    }

}