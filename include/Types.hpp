#ifndef TYPES_H
#define TYPES_H

#include <unordered_set>
#include <utility>
#include <vector>

typedef std::vector<int> Vect1DInt;
typedef std::vector<Vect1DInt> Vect2DInt;
typedef std::pair<int, int> IntPair;

// Custom hash function for std::pair<int, int>
namespace std {
    template <>
    struct hash<IntPair> {
        std::size_t operator()(const IntPair& p) const noexcept {
            return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
        }
    };
}

typedef std::vector<IntPair> VectIntPair;
typedef std::unordered_set<IntPair> SetIntPair;

enum class PlayerIDEnum { PLAYER_1, PLAYER_2, NONE };

enum class DirectionEnum { HORIZONTAL, VERTICAL };

enum class ComputerStrategyEnum { MONTE_CARLO, RANDOM_MOVE };

#endif  // TYPES_H