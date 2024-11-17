#include "../include/utility.hpp"

std::ostream &operator<<(std::ostream &os, const IntPair &value) {
    os << "(" << value.first << "," << value.second << ")";
    return os;
}