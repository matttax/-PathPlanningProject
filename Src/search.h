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

struct OpenCollection {
    std::map<std::pair<int, int>, Node*> coordinates;
    std::set<Node*, NodeComparator> nodes;
    void add(Node* node) {
        nodes.insert(node);
        coordinates.emplace(std::make_pair(node->i, node->j), node);
    }
    Node* find(std::pair<int, int> node_coordinates) {
        if (coordinates.count(node_coordinates))
            return coordinates[node_coordinates];
        return nullptr;
    }
    void removeFirst() {
        nodes.erase(nodes.begin());
    }
};

class Search
{
    public:
        Search();
        ~Search(void);
        SearchResult startSearch(ILogger *Logger, const Map &Map, const EnvironmentOptions &options);

    protected:
        SearchResult                    sresult; //This will store the search result
        std::list<Node>                 lppath, hppath; //
        OpenCollection                  OPEN;
        std::set<std::pair<int, int>>   CLOSED;

        static double heuristic(std::pair<int, int> coordinates, const EnvironmentOptions &options, const Map &map);
        void makePrimaryPath(Node* firstNode);
        void makeSecondaryPath();

        std::vector<std::pair<int, int>>  getChildren(Node* parent, const Map &map, const EnvironmentOptions& environment);
        void setNewWeight(Node *parent, Node *child);
};

#endif
