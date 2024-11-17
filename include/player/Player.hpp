#ifndef PLAYER_H
#define PLAYER_H

#include "../Types.hpp"
class Player {
public:
    Player(std::string name, PlayerIDEnum playerID);
    virtual ~Player() = default;
    virtual IntPair makeMove() = 0;  // Pure virtual for polymorphism
    std::string getName() const;
    PlayerIDEnum getPlayerID() const;

private:
    const std::string _playerName;
    const PlayerIDEnum _playerID;
};

typedef std::unique_ptr<Player> PlayerPtr;
typedef std::vector<PlayerPtr> PlayerList;

#endif  // PLAYER_H