#ifndef PLAYER
#define PLAYER

#include <string>

#include "enum_player.hpp"
#include "../utility.hpp"
#include "../graph/graph.hpp"

// TODO: Make sure all signatures are consistent (have argument names and types)
class IPlayer
{
public:
    virtual ~IPlayer()  = default;
    virtual std::string GetPlayerName() const = 0;
    virtual Player GetPlayerType() const = 0;
    virtual Pair DecideNextMove(Graph &) const = 0;
};

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

#endif // PLAYER