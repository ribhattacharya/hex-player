#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include <string>

#include "Player.hpp"
#include "../enums.hpp"
#include "../graph/graph.hpp"
#include "../custom_types.hpp"

class HumanPlayer : public Player
{

public:
    HumanPlayer(std::string name); 
    
    Pair decideNextMove(const Graph &g) const override;
};

#endif // HUMAN_PLAYER_H