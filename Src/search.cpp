#include "search.h"

Search::Search() {}

Search::~Search() {}


SearchResult Search::startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options) {
    int nodescreated = 1;
    int numberofsteps = 0;
    auto start_time = std::chrono::steady_clock::now();

    auto start_coordinates = map.getStart();
    auto goal_coordinates = map.getGoal();

    OPEN.add(new Node(start_coordinates.first, start_coordinates.second,
                      0, heuristic(start_coordinates, options, map), nullptr));
    while(!OPEN.nodes.empty()) {
        numberofsteps++;
        Node *curr = *OPEN.nodes.begin();
        if (curr->i == goal_coordinates.first && curr->j == goal_coordinates.second) {
            break;
        }
        std::vector<std::pair<int, int>> children = getChildren(curr, map, options);
        for (auto& child_coordinates : children) {
            if (CLOSED.count(child_coordinates)) {
                continue;
            }
            Node* wanted = OPEN.find(child_coordinates);
            if (wanted) {
                setNewWeight(curr, wanted);
            } else {
                Node* child = new Node(child_coordinates.first, child_coordinates.second,
                                       __INT_MAX__, heuristic(child_coordinates, options, map), curr);
                OPEN.add(child);
                nodescreated++;
                setNewWeight(curr, child);
            }
        }
        CLOSED.emplace(curr->i, curr->j);
        OPEN.removeFirst();
    }
    auto end_time = std::chrono::steady_clock::now();
    sresult.time = std::chrono::duration<double>(end_time - start_time).count();
    sresult.pathlength = (*OPEN.nodes.begin())->F;
    sresult.numberofsteps = numberofsteps;
    sresult.nodescreated = nodescreated;
    if (!OPEN.nodes.empty()) {
        sresult.pathfound = true;
        makePrimaryPath((*OPEN.nodes.begin()));
        makeSecondaryPath();
    }
    OPEN.nodes.clear();
    CLOSED.clear();
    sresult.hppath = &hppath;
    sresult.lppath = &lppath;
    return sresult;
}

void Search::setNewWeight(Node* parent, Node* child) {
    double len = 1;
    int dx = abs(parent->i - child->i);
    int dy = abs(parent->j - child->j);
    if (dx + dy == 2) {
        len *= CN_SQRT_TWO;
    }
    if (child->g > parent->g + len) {
        child->g = parent->g + len;
        child->F = child->g + child->h;
        child->parent = parent;
        OPEN.add(child);
    }
}

void Search::makePrimaryPath(Node* firstNode)
{
    lppath.push_front(*firstNode);
    Node* curr = firstNode;
    while (curr->parent) {
        lppath.push_front(*(curr->parent));
        curr = curr->parent;
    }
    lppath.push_front(*(curr));
}

void Search::makeSecondaryPath() {
    for (auto node : lppath) {
        if (hppath.size() >= 2) {
            auto last_node = hppath.back();
            auto prev_node = *std::prev(std::prev(hppath.end()));
            std::pair<int, int> dir1 = {last_node.i - prev_node.i, last_node.j - prev_node.j};
            std::pair<int, int> dir2 = {node.i - last_node.i, node.j - last_node.j};
            if (dir1.first * dir2.second == dir1.second * dir2.first) {
                hppath.pop_back();
            }
        }
        hppath.push_back(node);
    }
}

std::vector<std::pair<int, int>> Search::getChildren(Node* curr, const Map &map, const EnvironmentOptions& environment) {
    std::vector<std::pair<int, int>> moves = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    if (environment.allowdiagonal) {
        moves.insert(moves.end(), {{1, 1}, {-1, -1}, {1, -1}, {-1, 1}});
    }
    std::vector<std::pair<int, int>> children;

    for (auto [i_move, j_move] : moves) {
        int next_cell_i = curr->i + i_move;
        int next_cell_j = curr->j + j_move;
        if (!map.isWalkable(next_cell_i, next_cell_j)) {
            continue;
        }
        if (i_move * j_move != 0) {
            if (!environment.cutcorners) {
                if (map.isWalkable(curr->i, curr->j + j_move) && map.isWalkable(curr->i + i_move, curr->j))
                    children.emplace_back(next_cell_i, next_cell_j);
            } else if (!environment.allowsqueeze) {
                if (map.isWalkable(curr->i, curr->j + j_move) || map.isWalkable(curr->i + i_move, curr->j))
                    children.emplace_back(next_cell_i, next_cell_j);
            } else children.emplace_back(next_cell_i, next_cell_j);
        } else children.emplace_back(next_cell_i, next_cell_j);
    }
    return children;
}

double Search::heuristic(std::pair<int, int> coordinates, const EnvironmentOptions &options, const Map &map) {
    if (options.metrictype == 1)
        return 0;
    int dx = std::abs(map.getGoal().first - coordinates.first);
    int dy = std::abs(map.getGoal().second - coordinates.second);
    switch (options.metrictype) {
        case 0: return (std::abs(dx - dy) + CN_SQRT_TWO * std::min(dx, dy)) * options.hweight;
        case 1: return (dx + dy) * options.hweight;
        case 2: return std::sqrt(dx * dx + dy * dy) * options.hweight;
        case 3: return std::max(dx, dy) * options.hweight;
    }
    return 0;
}
