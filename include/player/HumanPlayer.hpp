#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.hpp"

class HumanPlayer : public Player {
public:
  HumanPlayer(std::string name, PlayerIDEnum playerID);
  IntPair makeMove() override; 
};

#endif // HUMANPLAYER_H