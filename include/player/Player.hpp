#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "../enums.hpp"
#include "../graph/graph.hpp"
#include "../custom_types.hpp"
#include "player_game_data.hpp"

class Player
{
private:
    std::string _playerName;
    PlayerType _playerType;

public:
    Player(std::string name, PlayerType type);
    virtual ~Player() {};
    virtual Pair decideNextMove(const Graph &g) const = 0;

    std::string getName() const;
    PlayerType getType() const;
};

typedef std::shared_ptr<Player> spPlayer;
typedef std::vector<std::shared_ptr<Player>> vspPlayer;

// void IPlayer::SetStarts(node_vect nodes)
// {
//     STARTS.clear();
//     STARTS.insert(nodes.begin(), nodes.end());
// }

// node_set &IPlayer::GetStarts() { return STARTS; }

// void IPlayer::SetGoals(node_vect nodes)
// {
//     GOALS.clear();
//     GOALS.insert(nodes.begin(), nodes.end());
// }

// node_set &IPlayer::GetGoals() { return GOALS; }

#endif // PLAYER_H