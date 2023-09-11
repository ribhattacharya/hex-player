#ifndef ABSTRACT_PLAYER
#define ABSTRACT_PLAYER

#include <unordered_map>
#include <unordered_set>
#include <string>
#include "enumPlayer.h"
#include "../utility.h"
#include "../graph.h"

using std::string;
using std::unordered_map;
using std::unordered_set;

class IPlayer
{
    Player playerType;
    string playerName;
    node_set STARTS, GOALS;

public:
    IPlayer(Player type, string nm) : playerType(type), playerName(nm) {}
    void SetStarts(node_vect);
    node_set &GetStarts();
    void SetGoals(node_vect);
    node_set &GetGoals();
    string GetPlayerName() const { return playerName; }
    Player GetPlayerType() const { return playerType; }

    // virtual void PassGraph(Graph &) = 0;
    virtual ~IPlayer() {}
    virtual Pair GetMove(Graph &) = 0;
};

void IPlayer::SetStarts(node_vect nodes)
{
    STARTS.clear();
    STARTS.insert(nodes.begin(), nodes.end());
}

node_set &IPlayer::GetStarts() { return STARTS; }

void IPlayer::SetGoals(node_vect nodes)
{
    GOALS.clear();
    GOALS.insert(nodes.begin(), nodes.end());
}

node_set &IPlayer::GetGoals() { return GOALS; }

#endif // ABSTRACT_PLAYER