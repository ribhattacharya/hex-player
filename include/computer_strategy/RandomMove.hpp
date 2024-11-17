#ifndef RANDOMMOVE_H
#define RANDOMMOVE_H

#include "../Types.hpp"
#include "../board/Board.hpp"
#include "ComputerStrategy.hpp"

class RandomMove : public ComputerStrategy{
public:
    IntPair calculateMove(const Board& board, PlayerIDEnum playerId) override;
};

#endif // RANDOMMOVE_H