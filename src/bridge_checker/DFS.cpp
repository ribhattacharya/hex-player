#include "bridge_checker/DFS.hpp"

#include "Types.hpp"
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
        IntPair start_pos, goal_pos;

        if (direction == DirectionEnum::HORIZONTAL) {
            start_pos = {i, 0};
            goal_pos = {i, graph.getSize() - 1};
        } else {
            start_pos = {0, i};
            goal_pos = {graph.getSize() - 1, i};
        }

        // Add start if it is owned by the player
        if (graph.getNodeOccupancy(start_pos) == playerId) {
            OPEN.push(graph.getNode(start_pos));
        }

        // Add goal if it is owned by the player
        if (graph.getNodeOccupancy(goal_pos) == playerId) {
            GOALS.insert(graph.getNode(goal_pos));
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
            if (!graph.nodeExists(neighbourID) ||
                !isValidNeighbour(neighbourID, graph.getSize(),
                                  graph.getSize()) ||
                graph.getNodeOccupancy(neighbourID) != playerId) {
                continue;
            }

            NodePtr neighbour = graph.getNode(neighbourID);
            // Check if the neighbour node is not owned by player or if it is
            // already visited
            // if (VISITED.find(neighbour) != VISITED.end()) {
            //     continue;
            // }

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