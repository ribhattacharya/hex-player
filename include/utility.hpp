#ifndef UTILITY_H
#define UTILITY_H

#include <ostream>
#include <unordered_set>
#include <vector>

#include "custom_types.hpp"
#include "graph/graph.hpp"

std::ostream &operator<<(std::ostream &os, const Pair &value);

std::ostream &operator<<(std::ostream &os, const uspNode &value);

std::ostream &operator<<(std::ostream &os, const vspNode &value);

void printGraph(const Graph &g);

#endif // UTILITY_H