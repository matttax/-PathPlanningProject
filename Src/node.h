#ifndef NODE_H
#define NODE_H

//That's the data structure for storing a single search node.
//You MUST store all the intermediate computations occuring during the search
//incapsulated to Nodes (so NO separate arrays of g-values etc.)

#include <tuple>

struct Node
{
    int     i, j; //grid cell coordinates
    double  F, g, h; //f-, g- and h-values of the search node
    Node    *parent; //backpointer to the predecessor node (e.g. the node which g-value was used to set the g-velue of the current node)

    Node(int i, int j, double g, double h, Node* parent) {
        this->i = i;
        this->j = j;
        this->g = g;
        this->h = h;
        F = g + h;
        this->parent = parent;
    }
};

struct NodeComparator {
    bool operator()(const Node* n1, const Node* n2) {
        return std::tie(n1->F, n1->i, n1->j) < std::tie(n2->F, n2->i, n2->j);
    }
};

#endif
