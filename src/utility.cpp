#include "../include/Utility.hpp"

std::ostream &operator<<(std::ostream &os, const IntPair &value) {
    os << "(" << value.first << "," << value.second << ")";
    return os;
}

void pause() {
    std::cout << "Press y to continue: ";
    char pause;
    std::cin >> pause;
}