#ifndef BOARD_H
#define BOARD_H

#include "disjointset.h"
#include "graph.h"
class Board {
    public:
        Board(int board_size);
        enum State{BLACK, WHITE, EMPTY };
        vector<State> grid;

        bool is_valid_entry(int row, int col, string player);

        void check_grid(int index, string player);
        void check_for_winner(int cell, string player);
        void bridge(int cell, size_t node, string player);
        friend ostream& operator<<(ostream& out, Board board);
        friend class AI;
        // Getters.
        string get_winner();
        int get_size();
    private:
        int size;
        string winner;

        // Each player builds up their own graph as they place pieces on the board.
        Graph graph_p1, graph_p2;
        DisjointSet union_p1, union_p2;
};

#endif
