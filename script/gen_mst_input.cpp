#include <iostream>
#include <fstream>
#include "MST.h"
using namespace std;

int main(){
    int n, m;
    vector<Edge> edgeList;
    cin >> n >> m;
    while(m--){
        int u, v, c;
        cin >> u >> v >> c;
        edgeList.push_back(Edge(u-1, v-1, c)); 
    }
    int l; cin >> l;
    vector<pair<int,int>> q;
    while(l--){
        int u, v;
        cin >> u >> v;
        q.push_back({u,v});
    }
    edgeList = build_MST(edgeList, n);


    cout << n << " " << n-1 << endl;    
    for(auto e : edgeList){
        cout << e.u+1 << " " << e.v+1 << " " << e.c << endl;
    }
    cout << (int) q.size() << endl;
    for(auto [u,v] : q){
        cout << u << " " << v << endl;
    }
}