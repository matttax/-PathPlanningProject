#ifndef NODE_H
#define NODE_H

//That's the data structure for storing a single search node.
//You MUST store all the intermediate computations occuring during the search
//incapsulated to Nodes (so NO separate arrays of g-values etc.)

struct Node
{
    int     i, j; //grid cell coordinates
    double  F, g, H; //f-, g- and h-values of the search node
    Node    *parent; //backpointer to the predecessor node (e.g. the node which g-value was used to set the g-velue of the current node)

    Node(int i, int j, double g, Node* parent) {
        this->i = i;
        this->j = j;
        this->g = g;
        this->parent = parent;
        F = this->g + this->H;
    }
};

struct NodeComparator {
    inline bool operator()(const Node* n1, const Node* n2) {
        return n1->g < n2->g;
    };
};

#endif
