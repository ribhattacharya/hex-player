#include <ostream>
#include <unordered_set>
#include <vector>

#include "../include/utility.hpp"
#include "../include/graph/node.hpp"

// TODO: Change these to shared_ptrs
std::ostream &operator<<(std::ostream &os, const Pair &value)
{
    os << "(" << value.first << "," << value.second << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::unordered_set<std::shared_ptr<Node> > &value)
{
    os << '(';
    for (auto val : value)
        os << val << ", ";
    os << ")\n";
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<std::shared_ptr<Node> > &value)
{
    os << '[';
    for (auto val : value)
        os << val << ", ";
    os << "]\n";
    return os;
}