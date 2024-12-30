#ifndef RANDOMMOVE_H
#define RANDOMMOVE_H

#include "../Types.hpp"
#include "../board/Board.hpp"
#include "ComputerStrategy.hpp"

class RandomMove : public ComputerStrategy{
private:
    IntPair _calculateMove(const Board& board, PlayerIDEnum curPlayerId) const override;
};

#endif // RANDOMMOVE_H