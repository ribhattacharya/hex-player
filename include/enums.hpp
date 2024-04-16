#ifndef ENUMS_H
#define ENUMS_H

enum class PlayerType
{
    HUMAN,
    COMP,
    NONE
};

enum class PlayerOrientation
{
    HORIZONTAL,
    VERTICAL
};

enum class ComputerLogic
{
    MONTE_CARLO,
    RANDOM_MOVE
};

#endif // ENUMS_H