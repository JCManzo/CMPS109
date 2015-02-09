//Pohl  generate a graph

//matrix representation
//calloc goes to new or use vector
//printf goes to use of "<<"
//struct becomes class
//advanced make_  becomes a constructor

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm> // used to reverse vector.

using namespace std;
// The following typedefs aren't needed when using c++
// typedef enum bool{FALSE = 0, TRUE = 1} bool: unneeded in C++
// typedef bool* ptr_bool;
// typedef ptr_bool* bool_matrix;

inline double probability(){ return (1.0 * rand()) / RAND_MAX; }

// For this project we'll say infinity = 32767
const int INF = 32767;

// struct graph has been converted to a class.
class Graph {
    int size;
    unsigned int range;
    bool** graph;

public:
    // Constructor declaration. Has no return type.
    Graph(int, double, int);
    void print_graph();
    bool is_connected();
    vector<int> dijkstra_undirectional(int, int);
    vector<int> dijkstra_bi(int,int);
};

// Constructor implementation. Replaces make_graph function.
Graph::Graph(int graph_size, double graph_density, int distance_range) {
    this->size = graph_size;
    this->range = distance_range;
    this->graph = new bool*[graph_size]();

    for(int i = 0; i < graph_size; ++i) {
       this->graph[i] =  new bool[graph_size]();
    }

    for(int i = 0; i < graph_size; ++i) {
       for(int j =0; j < graph_size; ++j) {
           if(probability() < graph_density) this->graph[i][j] = true;
       }
    }
}

// Backtracks through the path shortest path taken, insert to vector to return.
vector<int> get_path(int path[], int destination) {
    vector<int> shortest_path;
    // Add destination to our shortest path vector.
    shortest_path.push_back(destination);
     while(true) {
        int i = path[destination];
        if(i == INF) {
            break;
        } else {
            destination = i;
        }
        shortest_path.push_back(i);
    }

    // Reverses the vector for correct output.
    reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}

// Function performs dijkstra's (undirectional) algorithm given a starting node.
vector<int> Graph::dijkstra_undirectional(int source, int destination) {
    vector<int> shortest_path;

    if(this->is_connected() == true) {
        // Graph is connected. Run dijkstra's to return shortest path from vector source
        // vertex to destination vertex.
        cout << endl << "Graph is connected." << endl;
        int graph_size = this->size;
        // Initialize distance array of type int which will hold the shortest path.
        int distance[graph_size];

        // Keeps track of path taken to destination vertex.
        int path[graph_size];

        // Initialize visited array of type bool. Will be used to check if node has been visited.
        bool visited[graph_size];

        // Initializes a new matrix which will represent the weights between two connected
        // vertices of the same previously generated random graph.
        int weighted[graph_size][graph_size];

         for(int i = 0; i < graph_size; ++i) {
            for (int j = 0; j < graph_size; ++j) {
                weighted[i][j] = 0;
            }
         }
        // This checks to see if two nodes are connected. Two nodes are connected if graph[i][j] == 1
        // and graph[j][i] == 1. A nonnegative weight will be assigned randomly to the corresponding
        // node. Weight depends on range give by parameter in constructor method.
         for(int row = 0; row < graph_size; ++row) {
            for(int col = 0; col < graph_size; ++col) {
                if(col != row) {
                    // No loops in graph.
                    if(this->graph[row][col] == 1 && this->graph[col][row] == 1) {
                        int value = rand() % this->range;
                        weighted[row][col] = value;
                        weighted[col][row] = value;
                    }
                }
            }
        }

        // Step 1 and 2 of dijkstra's algoritm:
        // Initialize all distances between nodes to INF, all nodes are marked
        // as not being visited and the distance of the source node to 0.
        for (int i = 0; i < graph_size; ++i) {
            distance[i] = INF;
            visited[i] = false;
            path[i] = INF;
        }
        distance[source] = 0;

        // Step 3 -6 of dijkstra's:
        // For current node we check all its neighboors.
        for(int i = 0; i < graph_size; ++i) {
            // min will store path between two nodes with the lowest weight.
            int min = INF;
            for(int j = 0; j < graph_size; ++j) {
                if(!visited[j] && ((min == INF) || (distance[j] < distance[min]))) {
                    min = j;
                    // If the minimum weight vertex taken is also the destination vertex,
                    // we are done. Return the path.
                    if(min == destination) {
                       // cout << "Found " << min << ": " << distance[min] << endl;
                        cout << endl << "Cost of going from vertex " << source << " to vertex "
                             << destination << " is " << distance[min] << endl;
                        vector<int> graph_path = get_path(path, destination);
                        return graph_path;
                    }
                }
            }
            // Mark the taken path node as visited.
            visited[min] = 1;

            for(int i = 0; i < graph_size; ++i) {
                // Update the path weight.
                if(weighted[min][i] && distance[min] + weighted[min][i] < distance[i]) {
                    distance[i] = distance[min] + weighted[min][i];
                    path[i] = min;
                }
            }
        }

    return shortest_path;

    } else {
        //Graph is not connected. Return empty vector.
        cout << endl << "Graph is not connected. Run ./graph again to generate a new graph." << endl;
        return shortest_path;
     }
}

// implementation not working. Don't use.
vector<int> Graph::dijkstra_bi(int source, int destination) {
    vector<int> shortest_path;
    if(this->is_connected() == true) {
        // Graph is connected. Run dijkstra's to return shortest path from vector source
        // vertex to destination vertex.
        cout << endl << "Graph is connected." << endl;
        int graph_size = this->size;
        int destination2 = source;
        int source2 = destination;
        // Initialize distance array of type int which will hold the shortest path.
        int distance[graph_size];
        int distance2[graph_size];
        // Keeps track of path taken to destination vertex.
        int path[graph_size];
        int path2[graph_size];
        // Initialize visited array of type bool. Will be used to check if node has been visited.
        bool visited[graph_size];
        bool visited2[graph_size];
        // Initializes a new matrix which will represent the weights between two connected
        // vertices of the same previously generated random graph.
        int weighted[graph_size][graph_size];

         for(int i = 0; i < graph_size; ++i) {
            for (int j = 0; j < graph_size; ++j) {
                weighted[i][j] = 0;
            }
         }

        // This checks to see if two nodes are connected. Two nodes are connected if graph[i][j] == 1
        // and graph[j][i] == 1. A nonnegative weight will be assigned randomly to the corresponding
        // node. Weight depends on range give by parameter in constructor method.
         for(int row = 0; row < graph_size; ++row) {
            for(int col = 0; col < graph_size; ++col) {
                if(col != row) {
                    // No loops in graph.
                    if(this->graph[row][col] == 1 && this->graph[col][row] == 1) {
                        int value = rand() % this->range;
                        weighted[row][col] = value;
                        weighted[col][row] = value;
                    }
                }
            }
        }

        // Step 1 and 2 of dijkstra's algoritm:
        // Initialize all distances between nodes to INF, all nodes are marked
        // as not being visited and the distance of the source node to 0.
        for (int i = 0; i < graph_size; ++i) {
            distance[i] = INF;
            distance2[i] = INF;
            visited[i] = false;
            visited2[i] = false;
            path[i] = INF;
            path2[i] = INF;
        }
        distance[source] = 0;
        distance2[source2] = 0;
        // Step 3 -6 of dijkstra's:
        // For current node we check all its neighboors.
        vector<int> graph_path2;
        vector<int> graph_path;
        for(int i = 0; i < graph_size; ++i) {
            // min will store path between two nodes with the lowest weight.
            int min = INF;
            int min2 = INF;
            for(int j = 0; j < graph_size; ++j) {
                if(!visited[j] && ((min == INF) || (distance[j] < distance[min]))) {
                    min = j;
                    // If the minimum weight vertex taken is also the destination vertex,
                    // we are done. Return the path.
                   // if(min2 == min) {
                    //}
                    if(min == destination) {
                       // cout << "Found " << min << ": " << distance[min] << endl;
                        cout << endl << "Cost of going from vertex " << source << " to vertex "
                             << destination << " is " << distance[min] << endl;
                         graph_path = get_path(path, destination);

                    }
                }
             if(!visited2[j] && ((min2 == INF) || (distance2[j] < distance2[min2]))) {
                    min2 = j;
                    // If the minimum weight vertex taken is also the destination vertex,
                    // we are done. Return the path.
                   // if(min2 == min) {
                    //}
                    if(min2 == destination2) {
                       // cout << "Found " << min << ": " << distance[min] << endl;

                         graph_path2 = get_path(path2, destination2);
                       // shortest_path = graph_path2;
                    }
                }
            }

            // Mark the taken path node as visited.
            visited[min] = 1;
            visited2[min2] = 1;
            // Checks if a node visited in the backward run of dijkstra's already
            // exists in the forward search. Search ends here and we reurn the shortest_path;
            if(min == min2) {

                shortest_path = graph_path;
                return shortest_path;
            }
            for(int i = 0; i < graph_size; ++i) {
                if(weighted[min][i]) {
                    // Update the path weight.
                    if(distance[min] + weighted[min][i] < distance[i]) {
                        distance[i] = distance[min] + weighted[min][i];
                        path[i] = min;
                                    cout << "Min: " << min << endl;

                    }
                }
                if(weighted[min2][i]) {
                    // Update the path weight.
                    if(distance2[min2] + weighted[min2][i] < distance2[i]) {
                        distance2[i] = distance2[min2] + weighted[min2][i];
                        path2[i] = min2;
                                    cout << "Min2: " << min2 << endl;

                    }
                }
            }
        }
       /* for (int i = 0; i < graph_size; ++i) {
            cout << i  << ": " << distance[i] << endl;
        }*/
    return shortest_path;

    } else {
        //Graph is not connected. Return empty vector.
        cout << endl << "Graph is not connected. Run ./graph again to generate a new graph." << endl;
        return shortest_path;
     }
}

// Checks if a graph is connected. Is called before performing dijkstra's. Taken from
// Irah Pohl's lecture slides.
bool Graph::is_connected() {
    int old_size = 0;
    int c_size = 0;
    bool* close = new bool[this->size];
    bool* open = new bool[this->size];

    // Initialize all to false
    for(int i = 0; i < this->size; ++i) {
       open[i] = close[i] = false;
    }
    open[0] = true;

    while(c_size < this->size) {
        for(int i = 0; i < this->size; ++i) {
            old_size = c_size;
            // If vertex has not been previously visited, mark it as visited.
            if(open[i] && (close[i] == false)) {
                close[i] = true;
                c_size++;
                // Visit all adjacent vertices to the vertex.
                for(int j = 0; j < this->size; ++j)
                    open[j] = open[j] || this->graph[i][j];
                }
            }

        if(c_size == this->size) {
            return true;
        }
        if(old_size == c_size)  {
         return false;
        }
    }
    return false;
}

// Iterates over 2D array to display graph.
void Graph::print_graph() {
    cout << "graph size " << this->size << endl;

    for(int i = 0; i < this->size; ++i) {
        cout << endl;
        for(int j = 0; j < this->size; ++j) {
           cout << this->graph[i][j] << " ";
        }
    }
}
// Prints the shortest path vector that was returned from dijkstra's.
void print_path(vector<int> path) {
     cout << endl << "Shortest path is: ";
     for (vector<int>::iterator i = path.begin(); i != path.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
}

int main() {
    srand((unsigned)time( NULL ));
    cout << "Test simple graph generation" << endl;
    int source = rand() % (999);
    int destination = rand() % (999);
    int cost = rand() % 200;

    // Calls Graph's default constructor to create a new Graph object.
    Graph test1(1000, 0.1, cost);

    //test1.print_graph();
    vector<int> results = test1.dijkstra_undirectional(source, destination);

    // Prints the shortest path.
    if(test1.is_connected()) {
        print_path(results);
    }
    cout << endl << "END of TEST 1" << endl << endl;

    // Get new values for second graph test.
    source = rand() % (999);
    destination = rand() % (999);
    cost = rand() % 200;
    Graph test2(1000, 0.01, cost);

    //test2.print_graph();
    vector<int> results2 = test2.dijkstra_undirectional(source, destination);

    // Prints the shortest path.
    if(test2.is_connected()) {
        print_path(results2);
    }
    cout << endl << "END of TEST 2" << endl << endl;

    return 0;
}

