#ifndef TYPES_H
#define TYPES_H

#include <utility>
#include <vector>

typedef std::vector<int> Vect1DInt;
typedef std::vector<Vect1DInt> Vect2DInt;
typedef std::pair<int, int> IntPair;

enum class PlayerIDEnum
{
    PLAYER_1,
    PLAYER_2,
    NONE
};

enum class DirectionEnum
{
    HORICONTAL,
    VERTICAL
};

enum class ComputerStrategyEnum
{
    MONTE_CARLO,
    RANDOM_MOVE
};

#endif // TYPES_H