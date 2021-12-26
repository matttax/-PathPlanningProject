#ifndef SEARCH_H
#define SEARCH_H
#include "ilogger.h"
#include "searchresult.h"
#include "environmentoptions.h"
#include <list>
#include <vector>
#include <math.h>
#include <limits>
#include <chrono>
#include <set>
#include <map>
#include <type_traits>

//using Cmp = std::integral_constant<decltype(&NodeComparator), &NodeComparator>;

class Search
{
    public:
        Search();
        ~Search(void);
        SearchResult startSearch(ILogger *Logger, const Map &Map, const EnvironmentOptions &options);

    protected:
        //CODE HERE

        //Hint 1. You definetely need class variables for OPEN and CLOSE

        //Hint 2. It's a good idea to define a heuristic calculation function, that will simply return 0
        //for non-heuristic search methods like Dijkstra

        //Hint 3. It's a good idea to define function that given a node (and other stuff needed)
        //will return it's sucessors, e.g. unordered list of nodes

        //Hint 4. working with OPEN and CLOSE is the core
        //so think of the data structures that needed to be used, about the wrap-up classes (if needed)
        //Start with very simple (and ineffective) structures like list or vector and make it work first
        //and only then begin enhancement!


        SearchResult                    sresult; //This will store the search result
        std::list<Node>                 lppath, hppath; //
        std::vector<std::pair<int, int>>  getChildren(Node* parent, const Map &map, const EnvironmentOptions& environment);

        static double heuristic(int current_i, int current_j, const EnvironmentOptions &options, const Map &map);
        struct OPEN_COLLECTION {
            std::vector<Node*> nodes;
            void add(Node* node) {
                nodes.push_back(node);
                std::sort(nodes.begin(), nodes.end(), NodeComparator());
            }
            Node* find(std::pair<int, int> node_coordinates) {
                for (Node* curr : nodes) {
                    if (curr->i == node_coordinates.first && curr->j == node_coordinates.second)
                        return curr;
                }
                return nullptr;
            }
            void removeFirst() {
                nodes.erase(nodes.begin());
            }
        } OPEN;
        std::set<std::pair<int, int>>   CLOSED;
        void newWeight(Node *parent, Node *child, const Map &map);

        void makePrimaryPath(Node* firstNode);
        void makeSecondaryPath();
};

#endif
