#ifndef COMP_PLAYER
#define COMP_PLAYER

#include "IPlayer.h"

class CompPlayer : public IPlayer
{

public:
    CompPlayer(string name) : IPlayer(Player::COMP, name) {}
    ~CompPlayer() {}
    Pair GetMove(int) override;
};

Pair CompPlayer::GetMove(int SIZE)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range for the distribution
    std::uniform_int_distribution<> dis(0, SIZE-1);

    // Generate a single random integer
    int row = dis(gen), col = dis(gen);

    return std::make_pair(row, col);
}

#endif // COMP_PLAYER