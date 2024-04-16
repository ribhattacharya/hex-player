#include "../../include/graph/node.hpp"

Node::Node(int i, int j, int id) : _IDX(std::make_pair(i, j)), _ID(id), _player(Player::NONE) {}

Pair Node::getIDX() const { return _IDX; }

int Node::getID() const { return _ID; }

Player Node::getPlayer() { return _player; }

void Node::setPlayer(Player p) { _player = p; }

vspNode Node::getNeighbours() { return _neighbours; }

void Node::setNeighbours(vspNode &neighbours) { this->_neighbours = neighbours; }