#ifndef ABSTRACT_PLAYER
#define ABSTRACT_PLAYER

#include <unordered_map>
#include <unordered_set>
#include <string>
#include "enumPlayer.h"
#include "../utility.h"

using std::string;
using std::unordered_map;
using std::unordered_set;

class IPlayer
{
    Player playerType;
    string playerName;
    unordered_set<Node *> STARTS, GOALS;

public:
    IPlayer(Player type, string nm) : playerType(type), playerName(nm) {}
    void SetStarts(vector<Node *>);
    unordered_set<Node *> &GetStarts();
    void SetGoals(vector<Node *>);
    unordered_set<Node *> &GetGoals();
    string GetPlayerName() const { return playerName; }
    Player GetPlayerType() const { return playerType; }

    virtual ~IPlayer()
    {
        STARTS.clear();
        GOALS.clear();
    }
    virtual Pair GetMove(int) = 0;
};

void IPlayer::SetStarts(vector<Node *> nodes)
{
    for (auto start : nodes)
        STARTS.insert(start);
}

unordered_set<Node *> &IPlayer::GetStarts() { return STARTS; }

void IPlayer::SetGoals(vector<Node *> nodes)
{
    for (auto goal : nodes)
        GOALS.insert(goal);
}

unordered_set<Node *> &IPlayer::GetGoals() { return GOALS; }

#endif // ABSTRACT_PLAYER