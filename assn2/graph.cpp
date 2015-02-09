//Pohl  generate a graph

//matrix representation
//calloc goes to new or use vector
//printf goes to use of "<<"
//struct becomes class
//advanced make_  becomes a constructor

#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;
// The following typedefs aren't needed when using c++
// typedef enum bool{FALSE = 0, TRUE = 1} bool: unneeded in C++
// typedef bool* ptr_bool;
// typedef ptr_bool* bool_matrix;

inline double probability(){ return (1.0 * rand()) / RAND_MAX; }

// struct graph has been converted to a class.
class Graph {
    int size;
    bool** g1;
public:
    // Constructor declaration. Has no return type.
    Graph(int, double);
    void print_graph();
};

// Constructor implementation. Replaces make_graph function.
Graph::Graph(int graph_size, double graph_density) {
    // "this" is a special type of pointer that points to the current object.
    // It's optional but I prefer to use it to make object members more obvious.
    this->size = graph_size;
    this->g1 = new bool*[graph_size]();

    for(int i = 0; i < graph_size; ++i) {
       this->g1[i] =  new bool[graph_size]();
    }

    for(int i = 0; i < graph_size; ++i) {
       for(int j =0; j < graph_size; ++j) {
           if(probability() < graph_density) this->g1[i][j] = true;
       }
    }
}

// Iterates over 2D array to display graph.
void Graph::print_graph() {
    cout << "graph size " << this->size << endl;

    for(int i = 0; i < this->size; ++i) {
        cout << endl;
        for(int j = 0; j < this->size; ++j) {
           cout << this->g1[i][j] << "\t";
        }
    }
}

int main() {
    srand((unsigned)time( NULL ));
    cout << "Test simple graph generation" << endl;

    // Calls Graph's default constructor to create a new Graph object.
    Graph test1(10, 0.7);
    test1.print_graph();
    cout << endl << "END of TEST 1" << endl << endl;
    Graph test2(8, 0.5);
    test2.print_graph();
    cout << endl << "END of TEST 2" << endl << endl;

    return 0;
}

