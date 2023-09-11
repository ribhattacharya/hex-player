#ifndef UTILITY_H
#define UTILITY_H

#include<unordered_set>
#include<vector>
// #include "node.h"

class Node;

using std::unordered_set;
using std::vector;

typedef std::pair<int, int> Pair;
typedef unordered_set<Node *> node_set;
typedef vector<Node *> node_vect;

std::ostream& operator<<(std::ostream& os, const Pair& value) {
    os << "(" << value.first << "," << value.second << ")";
    return os;
}

#endif // UTILITY_H