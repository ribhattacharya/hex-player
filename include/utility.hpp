#ifndef UTILITY_H
#define UTILITY_H

#include <ostream>
#include <unordered_set>
#include <vector>

#include "custom_types.hpp"
#include "graph/node.hpp"

std::ostream &operator<<(std::ostream &os, const Pair &value);

std::ostream &operator<<(std::ostream &os, const std::unordered_set<std::shared_ptr<Node> > &value);

std::ostream &operator<<(std::ostream &os, const std::vector<std::shared_ptr<Node> > &value);

#endif // UTILITY_H