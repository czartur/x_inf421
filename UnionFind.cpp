#include "UnionFind.h"


UnionFind::UnionFind(int n){
    size.assign(n,0);
    for(int i=0; i<n; i++) par.push_back(i);
}

int UnionFind::find(int a) { return par[a] == a ? a : par[a] = find(par[a]); }

void UnionFind::unite(int a, int b){
    
    // compare set representatives
    if((a = find(a)) == (b = find(b))) return; 

    // link smallest to largest
    if(size[a] < size[b]) swap(a,b); // a >= b alway
    par[b] = a;
    size[a] += size[b]; 
}

bool UnionFind::isSame(int a, int b) { return find(a) == find(b); }