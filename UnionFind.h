#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>
using namespace std;

class UnionFind{
    private:
    vector<int> par, size;

    public:
    UnionFind(int n);

    int find(int a);

    void unite(int a, int b);

    bool isSame(int a, int b);
};

#endif