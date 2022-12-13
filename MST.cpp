#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Prim's algo for MST
// INPUT : Graph G
// OUTPUT : Tree T

class Edge{ 
    public :
    int u; // first vertice
    int v; // second vertice
    int c; // weight
    
    Edge(int n_u, int n_v, int n_c) : u{n_u}, v{n_v}, c{n_c} {};
   
    bool operator<(const Edge& edge) const {
        return make_pair(c, make_pair(v, u)) > make_pair(edge.c, make_pair(edge.v, edge.u)); // inverse order sorting
    }

    friend ostream& operator<<(ostream& os, const Edge& edge);
};

ostream&  operator<<(ostream&os, const Edge& edge){
    os << edge.u << " <--[" << edge.c << "]--> " << edge.v;
    return os;
}

vector<Edge> MST(vector<vector<pair<int,int>>> &adj){
    //int n = (int) adj.size();
    
    vector<Edge> tree;
    vector <bool> vis((int)adj.size());

    priority_queue<Edge> pq;
    pq.push(Edge(0,0,-1));

    while(!pq.empty()){
        Edge edge = pq.top();
        int u = pq.top().u, v = pq.top().v;
        pq.pop();
        
        if(vis[v]) continue;
        vis[v] = true;
        if(edge.c != -1) tree.push_back(edge);

        for(auto cur : adj[v]){
            if(vis[cur.second]) continue;
            pq.push(Edge(v, cur.first, cur.second));
        }
    }

    return tree;
}

vector<vector<pair<int,int>>> to_adj_list(vector<Edge> &edge_list, int n){
    vector<vector<pair<int,int>>> ans(n);
    for(auto edge : edge_list){
        ans[edge.u].push_back({edge.v, edge.c});
        ans[edge.v].push_back({edge.u, edge.c});
    }
    return ans;
}

void print(vector<Edge> tree){
    for(auto edge : tree) cout << edge << endl;
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    while(m--){
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v,c});
        adj[v].push_back({u,c});
    }

    vector<Edge> tree = MST(adj);
    print(tree);
}