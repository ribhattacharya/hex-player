#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

#include <vector>
#include <unordered_set>
#include <queue>

class Node; // forward declarion so that typedefs can be defined

typedef std::pair<int, int> Pair;

typedef std::shared_ptr<Node> spNode;
typedef std::vector<spNode> vspNode;
typedef std::vector<vspNode> vvspNode;
typedef std::unordered_set<spNode> uspNode;
typedef std::queue<spNode> qspNode;

#endif // CUSTOM_TYPES_H