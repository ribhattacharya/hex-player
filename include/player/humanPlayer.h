#ifndef HUMAN_PLAYER
#define HUMAN_PLAYER

#include <iostream>
#include "IPlayer.h"

using std::cin;
using std::cout;

class HumanPlayer : public IPlayer
{

public:
    HumanPlayer(string name) : IPlayer(Player::HUMAN, name) {}
    ~HumanPlayer() {}
    Pair GetMove(int) override;
};

Pair HumanPlayer::GetMove(int SIZE)
{
    char row = 'a', col = 'a';
    cout << "Enter row: ";
    cin >> row;
    cout << "Enter column: ";
    cin >> col;

    int i = row - 'a', j = col - 'a';

    // Convert 1-indexed rows and columns into 0-indexed
    return std::make_pair(i, j);
}

#endif // HUMAN_PLAYER