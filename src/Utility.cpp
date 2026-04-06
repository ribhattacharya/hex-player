#include "Utility.hpp"

std::ostream& operator<<(std::ostream& os, const IntPair& value) {
    os << "(" << value.first << "," << value.second << ")";
    return os;
}

void pause() {
    std::cout << "Press y to continue: ";
    char pause;
    std::cin >> pause;
}

// ANSI color codes
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string BLUE = "\033[34m";
const std::string YELLOW = "\033[33m";
const std::string CYAN = "\033[36m";
const std::string MAGENTA = "\033[35m";
const std::string RESET = "\033[0m";

// Text formatting
const std::string BOLD = "\033[1m";
const std::string DIM = "\033[2m";
const std::string BLINK = "\033[5m";
const std::string REVERSE = "\033[7m";

// Special effects
const std::string BLINKING_GREEN_HIGHLIGHT = "\033[5;42m";
