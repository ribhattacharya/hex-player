#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#include "../../include/board/board.hpp"
#include "../../include/graph/node.hpp"
#include "../../include/player/Player.hpp"
#include "../../include/utility.hpp"

using std::cout;
using std::endl;
using std::string;

Board::Board(const int size, vspPlayer players) : _SIZE(size), _g(size), _players(players)
{
    // cout << "Main graph address: " << &_g << '\n';
    // assert(this->_players.size() == 2);

    _initPlayerGameData(_players[0], PlayerOrientation::VERTICAL);
    _initPlayerGameData(_players[1], PlayerOrientation::HORIZONTAL);

    // for (auto player : _players)
    // {
    //     if (player->GetPlayerType() == Player::COMP)
    //     {
    //         Graph gCopy(_g);
    //         cout << "Argyument before passing address: " << &gCopy << '\n';
    //         player->PassGraph(gCopy);
    //     }
    // }

    printGraph(_g);
}

void Board::_initPlayerGameData(spPlayer player, PlayerOrientation orientation)
{
    uspNode starts, goals;
    for (int k = 0; k < _SIZE; k++)
    {
        Pair startIdx, goalIdx;

        if (orientation == PlayerOrientation::VERTICAL)
        {
            startIdx = std::make_pair(0, k);
            goalIdx = std::make_pair(_SIZE - 1, k);
        }
        else if (orientation == PlayerOrientation::HORIZONTAL)
        {
            startIdx = std::make_pair(k, 0);
            goalIdx = std::make_pair(k, _SIZE - 1);
        }

        starts.insert(_g.getNode(startIdx));
        goals.insert(_g.getNode(goalIdx));
    }

    PlayerGameData playerGameData(orientation, starts, goals);
    _playersGameData[player] = playerGameData;
}

bool Board::_checkWinner(spPlayer player)
{
    auto starts = _playersGameData[player].getStarts();
    auto goals = _playersGameData[player].getGoals();
    auto playerType = player->getType();
    return _g.isBridgeFormed(starts, goals, playerType);
}

void Board::_makeMove(spPlayer player)
{
    // Graph gCopy(_g);
    Pair idx = player->decideNextMove(_g);

    while (!_g.isAvailable(idx))
    {
        std::cout << idx << "Node not available, try again!\n";
        idx = player->decideNextMove(_g);
    }
    

    PlayerType playertype = player->getType();
    _g.setPlayer(idx, playertype);

    std::cout << "\x1B[2J\x1B[H"; // Clear screen
    printGraph(_g);
}

//TODO: Fix bug where computer loses on first move
void Board::playGame()
{
    // By nature of game, it cannot end in draw, so it will terminate.
    while (true)
    {   int instance = 0;
        for (auto player : _players)
        {   
            _makeMove(player);
            // cout << "make move" << ++instance << "\n";
            // Graph gCopy(_g);
            // cout << "Argument before passing address: " << &gCopy << '\n';
            // _players[1]->PassGraph(gCopy);

            if (_checkWinner(player))
            {
                cout << '\n' << player->getName() << " wins!\n";
                return;
            }
        }
    }

    cout << "\nGame ends in a draw! There's something WRONG!" << endl;
    return;
}

// TODO: Make printing symbols instance based rather than enum based
// void Board::printGraph() const
// {

//     unordered_map<Player, char> symbols = {
//         {Player::HUMAN, 'X'},
//         {Player::COMP, 'O'},
//         {Player::NONE, '.'}};

//     cout << string(3, ' ');
//     for (int col = static_cast<int>('a'), j = 0; j < _SIZE; j++, col++)
//     {
//         cout << '|' << static_cast<char>(col) << '|';
//         if (j != _SIZE - 1)
//             cout << string(1, ' ');
//     }
//     cout << "\n";

//     for (int margin = 0, i = 0, row = static_cast<int>('a'); i < _SIZE; i++, row++)
//     {
//         cout << string(margin++, ' ');
//         cout << '|' << static_cast<char>(row) << '|' << string(1, ' ');
//         for (int j = 0; j < _SIZE; j++)
//         {
//             Pair idx = std::make_pair(i, j);
//             Player p = _g.GetNode(idx)->GetPlayer();
//             const char player_symbol = symbols[p];

//             cout << player_symbol;
//             if (j != _SIZE - 1)
//                 cout << " - ";
//         }
//         cout << '\n';
//         if (i != _SIZE - 1)
//         {
//             cout << string(margin++ + 4, ' ');
//             for (int j = 0; j < _SIZE - 1; j++)
//             {
//                 cout << "\\ / ";
//             }
//             cout << "\\" << '\n';
//         }
//     }
// }

// void Board::printGraphData() const
// {
//     cout << "Node # "
//          << " Neighbours" << endl;
//     for (int i = 0; i < _SIZE; i++)
//     {
//         for (int j = 0; j < _SIZE; j++)
//         {
//             cout << left << setw(8) << _g.GetNode(std::make_pair(i, j))->GetID();
//             for (const auto neighbour : _g.GetNode(std::make_pair(i, j))->GetNeighbours())
//                 cout << neighbour->GetID() << " ";
//             cout << endl;
//         }
//     }
// }

