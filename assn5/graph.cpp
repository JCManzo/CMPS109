#include "graph.h"

// Default constructor
Graph::Graph() {
    this->size = 0;
}

// Creates a Graph with size (graph_size*graph_size).
Graph::Graph(int graph_size) {
    this->size = 0;

    this->Vertices.reserve(graph_size);
    this->Edges.reserve(graph_size);

    for(int i = 0; i < graph_size; ++i) {
        this->Vertices.push_back(i);
    }

    for(int i =0; i < graph_size; ++i) {
        this->Edges.push_back(map<int, int>());
    }
}

// Return number of edges in a graph;
int Graph::get_edge_count() {
    return size;
}

// Return number of vertices in a graph.
int Graph::get_vertex_count() {
    return Vertices.size();
}

// Returns all the edges of a vertexl
map<int, int>& Graph::get_edges(int vertex) {
    return this->Edges[vertex];
}

// Returns a vector containing the vertices in this graph.
vector<int> Graph::get_vertices() {
    return this->Vertices;
}

// Iterates vector containing graph vertices searching the given vertex.
bool Graph::find_vertex(int vertex) {
    vector<int>::iterator it;
    for(it = Vertices.begin(); it != Vertices.end();  ++it) {
        if(*it == vertex) {
           return true;
        }
    }
    return false;
}

// Adds an edge between the given two vertices. Cannot create a loop (vertex to a vertexr)
bool Graph::add_edge(int v, int u, int weight) {
    if(v == u) {
        return false;
    }
    pair<int, int> adj_list(u,weight);

    if(this->find_vertex(v) && this->find_vertex(u)) {
        this->Edges[v].insert(adj_list);
        this->size++;
        return true;
    }
    return false;
}
