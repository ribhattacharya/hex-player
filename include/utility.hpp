#ifndef UTILITY
#define UTILITY

#include <ostream>
#include <unordered_set>
#include <vector>

#include "../include/custom_types.hpp"
#include "../include/node.hpp"

std::ostream &operator<<(std::ostream &os, const Pair &value);

std::ostream &operator<<(std::ostream &os, const std::unordered_set<Node *> &value);

std::ostream &operator<<(std::ostream &os, const std::vector<Node *> &value);

#endif // UTILITY