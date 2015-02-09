#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>
#include "graph.h"

// Union-find algorithm for disjoint sets.
class DisjointSet {
    public:
        void union_set(int cell, int neighbor);
        DisjointSet(int size);
        int find_set(int node);

        bool is_connected(int cell, int neighbor);
    private:
        vector<int> height, parent;
};

#endif
