#ifndef UTILITY
#define UTILITY

#include <unordered_set>
#include <vector>

class Node;

// TODO: Change these to shared_ptrs
typedef std::pair<int, int> Pair;
typedef std::unordered_set<Node *> node_set;
typedef std::vector<Node *> node_vect;

std::ostream &operator<<(std::ostream &os, const Pair &value)
{
    os << "(" << value.first << "," << value.second << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, const node_set &value)
{
    os << '(';
    for (auto val : value)
        os << val << ", ";
    os << ")\n";
    return os;
}

std::ostream &operator<<(std::ostream &os, const node_vect &value)
{
    os << '[';
    for (auto val : value)
        os << val << ", ";
    os << "]\n";
    return os;
}

#endif // UTILITY