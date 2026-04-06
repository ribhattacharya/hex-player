#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>

#include "Types.hpp"

using std::cout;
using std::string;

std::ostream& operator<<(std::ostream& os, const IntPair& value);

void pause();

// ANSI color codes
extern const std::string RED;
extern const std::string GREEN;
extern const std::string BLUE;
extern const std::string YELLOW;
extern const std::string CYAN;
extern const std::string MAGENTA;
extern const std::string RESET;

// Text formatting
extern const std::string BOLD;
extern const std::string DIM;
extern const std::string BLINK;
extern const std::string REVERSE;

// Special effects
extern const std::string BLINKING_GREEN_HIGHLIGHT;

#endif  // UTILITY_H
