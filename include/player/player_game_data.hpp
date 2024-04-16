#ifndef PLAYER_GAME_DATA_H
#define PLAYER_GAME_DATA_H

#include "../enums.hpp"
#include "../graph/node.hpp"

class PlayerGameData
{
private:
    PlayerOrientation _ORIENTATION;
    uspNode STARTS, GOALS;

public:
    PlayerGameData() {}
    PlayerGameData(PlayerOrientation orientation, uspNode starts, uspNode goals);
    PlayerGameData(const PlayerGameData& other);   
    PlayerOrientation getOrientation() const;
    uspNode getStarts() const;
    uspNode getGoals() const;
};

#endif // PLAYER_GAME_DATA_H