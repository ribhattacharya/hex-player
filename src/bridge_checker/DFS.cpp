#include "bridge_checker/DFS.hpp"
#include "graph/Node.hpp"

DFS::DFS() {
}

bool DFS::isValidNeighbour(const IntPair &nodeID, const int MAX_ROWS,
                           const int MAX_COLS) const {
    return nodeID.first >= 0 && nodeID.first < MAX_ROWS && nodeID.second >= 0 &&
           nodeID.second < MAX_COLS;
}

bool DFS::isBridgeFormed(const Graph &graph, PlayerIDEnum playerId,
                         DirectionEnum direction) {
    NodePtrStack OPEN;
    NodePtrSet GOALS, VISITED;

    // Add starts and goals
    for (int i = 0; i < graph.getSize(); i++) {
        // Add starts
        NodePtr start(nullptr), goal(nullptr);

        if (direction == DirectionEnum::HORIZONTAL) {
            start = graph.getNode({i, 0});
            goal = graph.getNode({i, graph.getSize() - 1});
        } else {
            start = graph.getNode({0, i});
            goal = graph.getNode({graph.getSize() - 1, i});
        }

        // Add start if it is owned by the player
        if (start->getOccupancy() == playerId) {
            OPEN.push(start);
        }

        // Add goal if it is owned by the player
        if (goal->getOccupancy() == playerId) {
            GOALS.insert(goal);
        }
    }

    // 6 directions
    Vect2DInt delta{{0, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 0}, {1, -1}};

    // DFS
    while (!OPEN.empty() && !GOALS.empty()) {
        NodePtr node = OPEN.top();
        OPEN.pop();
        // std::cout << "Visiting node " << node->getID() << std::endl;
        // Check if the node is already visited, since a START neighbour can be
        // added to the stack AGAIN during DFS.
        if (VISITED.find(node) != VISITED.end()) {
            continue;
        }
        VISITED.insert(node);

        for (const auto &dir : delta) {
            IntPair neighbourID = {node->getID().first + dir[0],
                                   node->getID().second + dir[1]};
            // Check if the neighbour node exists
            if (!isValidNeighbour(neighbourID, graph.getSize(),
                                  graph.getSize())) {
                continue;
            }

            NodePtr neighbour = graph.getNode(neighbourID);
            // Check if the neighbour node is owned by the player or if it is
            // already visited
            if (neighbour->getOccupancy() != playerId ||
                VISITED.find(neighbour) != VISITED.end()) {
                continue;
            }

            // Check if the neighbour node is a goal
            if (GOALS.find(neighbour) != GOALS.end()) {
                // std::cout << "Final node    " << node->getID() << std::endl;
                return true;
            }

            OPEN.push(neighbour);
        }
    }
    return false;
}