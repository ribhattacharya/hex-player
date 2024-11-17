#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>

#include "Types.hpp"

using std::cout;
using std::string;

std::ostream &operator<<(std::ostream &os, const IntPair &value);

#endif  // UTILITY_H
