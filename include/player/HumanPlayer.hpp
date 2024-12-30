#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player/Player.hpp"

class HumanPlayer : public Player {
public:
    HumanPlayer(std::string name, PlayerIDEnum playerID);
    IntPair getMove(const Board& board) const override;
};

#endif  // HUMANPLAYER_H