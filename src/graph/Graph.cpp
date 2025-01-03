#include "graph/Graph.hpp"

#include <stdexcept>

#include "graph/Node.hpp"

Graph::Graph(int size) : _size(size), _nodePointersMap() {
}

Graph::Graph(const Graph &other) : _size(other._size) {
    for (auto &nodePointer : other._nodePointersMap) {
        _nodePointersMap[nodePointer.first] =
            std::make_shared<Node>(*nodePointer.second);
    }
}

int Graph::getSize() const {
    return _size;
}

PlayerIDEnum Graph::getNodeOccupancy(IntPair &pos) const {
    if (nodeExists(pos)) {
        return _nodePointersMap.at(pos)->getOccupancy();
    }
    return PlayerIDEnum::NONE;
}

void Graph::setNodeOccupancy(IntPair &pos, PlayerIDEnum playerId) {
    if (nodeExists(pos)) {
        _nodePointersMap[pos]->setOccupancy(playerId);
    } else {
        _nodePointersMap[pos] =
            std::make_shared<Node>(pos.first, pos.second, playerId);
    }
}

NodePtr Graph::getNode(IntPair &pos) const {
    if (nodeExists(pos)) {
        return _nodePointersMap.at(pos);
    }
    throw std::runtime_error("Node does not exist at position (" +
                             std::to_string(pos.first) + ", " +
                             std::to_string(pos.second) + ")");
}

bool Graph::nodeExists(IntPair &pos) const {
    return _nodePointersMap.find(pos) != _nodePointersMap.end();
}