#include "../../include/graph/Graph.hpp"
#include "../../include/graph/Node.hpp"

Graph::Graph(int size) : _size(size) {
    _nodes.resize(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            _nodes[i].emplace_back(Node(i, j));
        }
    }
}

Graph::Graph(const Graph &other) : _size(other._size) {
    _nodes.resize(_size);
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            _nodes[i].emplace_back(other._nodes[i][j]);
        }
    }
}

PlayerIDEnum Graph::getNodeOccupancy(IntPair pos) const {
    return _nodes[pos.first][pos.second].getOccupancy();
}

void Graph::setNodeOccupancy(IntPair pos, PlayerIDEnum playerId) {
    _nodes[pos.first][pos.second].setOccupancy(playerId);
}