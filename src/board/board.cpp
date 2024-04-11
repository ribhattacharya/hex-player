#include<vector>

#include "include/board/board.hpp"
#include "include/node.hpp"
#include "include/player/IPlayer.hpp"
#include "include/utility.hpp"

using std::vector;
using std::cout;

Board::Board(int s, std::vector<std::shared_ptr<IPlayer>> players) : _SIZE(s), _g(s)
{
    cout << "Main graph address: " << &_g << '\n';
    this->_players = players;

    // assert(this->_players.size() == 2);

    SaveStartAndGoalNodes(_players[1], "vertical");
    SaveStartAndGoalNodes(_players[0], "horizontal");

    // for (auto player : _players)
    // {
    //     if (player->GetPlayerType() == Player::COMP)
    //     {
    //         Graph gCopy(_g);
    //         cout << "Argyument before passing address: " << &gCopy << '\n';
    //         player->PassGraph(gCopy);
    //     }
    // }

    _g.printGraph();
}

void Board::_saveStartAndGoalNodes(std::shared_ptr<IPlayer> player, string orientation)
{
    vector<Node *> starts(_SIZE), goals(_SIZE);

    for (int k = 0; k < _SIZE; k++)
    {
        Pair startIdx, goalIdx;

        if (orientation == "vertical")
        {
            startIdx = std::make_pair(0, k);
            goalIdx = std::make_pair(_SIZE - 1, k);
        }
        else if (orientation == "horizontal")
        {
            startIdx = std::make_pair(k, 0);
            goalIdx = std::make_pair(k, _SIZE - 1);
        }

        starts[k] = _g.GetNode(startIdx);
        goals[k] = _g.GetNode(goalIdx);
    }

    player->SetStarts(starts);
    player->SetGoals(goals);
}

bool Board::_checkWinner(std::shared_ptr<IPlayer> player) const
{
    node_set STARTS = player->GetStarts();
    node_set GOALS = player->GetGoals();
    Player playerType = player->GetPlayerType();

    return _g.IsBridgeFormed(STARTS, GOALS, playerType);
}

void Board::_makeMove(std::shared_ptr<IPlayer> player)
{
    Graph gCopy(_g);
    Pair idx = player->GetMove(gCopy);

    while (!_g.IsAvailable(idx))
    {
        cout << idx << "Node not available, try again!\n";
        idx = player->GetMove(gCopy);
    }
    

    Player playertype = player->GetPlayerType();
    _g.SetPlayer(idx, playertype);

    std::cout << "\x1B[2J\x1B[H"; // Clear screen
    _g.printGraph();
}

void Board::playGame()
{
    // By nature of game, it cannot end in draw, so it will terminate.
    while (true)
    {   int instance = 0;
        for (auto player : _players)
        {   
            MakeMove(player);
            // cout << "make move" << ++instance << "\n";
            // Graph gCopy(_g);
            // cout << "Argument before passing address: " << &gCopy << '\n';
            // _players[1]->PassGraph(gCopy);

            if (checkWinner(player))
            {
                cout << '\n' << player->GetPlayerName() << " wins!\n";
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

// TODO: Move printing to utility class
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

