#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Graph {
    public:
        // Constructors
        Graph();
        Graph(int graph_size);

        bool add_edge(int v, int u, int weight);
        bool find_vertex(int v);

        // Getters.
        int get_vertex_count();
        int get_edge_count();
        vector<int> get_vertices();
        map<int, int>& get_edges(int v);
    private:
        int size;

        vector<int> Vertices;
        vector<map<int, int> > Edges;
};

#endif
