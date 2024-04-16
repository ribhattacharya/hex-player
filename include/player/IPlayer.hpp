#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "../enums.hpp"
#include "../graph/graph.hpp"
#include "../custom_types.hpp"

class IPlayer
{
public:
    virtual ~IPlayer() {};
    virtual std::string getPlayerName() const = 0;
    virtual Player getPlayerType() const = 0;
    virtual Pair decideNextMove(const Graph &g) const = 0;
};

typedef std::shared_ptr<IPlayer> spIPlayer;
typedef std::vector<std::shared_ptr<IPlayer>> vspIPlayer;

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