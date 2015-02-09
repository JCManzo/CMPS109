#include "disjointset.h"

// Union-find algorithm for disjoint sets. Pseudo-code used from
// https://www.cse.ust.hk/~dekai/271/notes/L09/L09.pdf

// Constructor
DisjointSet::DisjointSet(int size) {
    parent.reserve(size);
    height.reserve(size);

    for(int i = 0 ; i < size; ++i) {
        parent.push_back(i);
        height.push_back(1);
    }
}

// Traces parent until the root is reached then returns that root.
int DisjointSet::find_set(int node) {
    while(parent[node] != node)
        node = parent[node];
    return node;
}

// Joins the two nodes.
void DisjointSet::union_set(int cell, int neighbor) {
    int a = find_set(cell);
    int b = find_set(neighbor);

    if(height[a] < height[b]) {
        parent[a] = b;
        height[a] += height[b];
    } else {
        parent[b] = a;
        height[b] += height[a];
    }
}

// Checks if parent of node (same set)
bool DisjointSet::is_connected(int cell, int neighbor) {
    return find_set(cell) == find_set(neighbor);
}
