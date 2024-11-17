#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.hpp"

class HumanPlayer : public Player {
public:
  HumanPlayer(std::string name, PlayerIDEnum playerID);
  IntPair makeMove(const Board& board) override; 
};

#endif // HUMANPLAYER_H