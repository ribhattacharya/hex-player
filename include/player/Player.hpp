#ifndef PLAYER_H
#define PLAYER_H

#include "../Types.hpp"
#include "../board/Board.hpp"

class Player {
public:
    Player(std::string name, PlayerIDEnum playerID);
    virtual ~Player() = default;
    virtual IntPair getMove(const Board& board) const = 0;
    std::string getName() const;
    PlayerIDEnum getPlayerID() const;

private:
    const std::string _playerName;
    const PlayerIDEnum _playerID;
};

typedef std::unique_ptr<Player> PlayerPtr;
typedef std::vector<PlayerPtr> PlayerList;

#endif  // PLAYER_H