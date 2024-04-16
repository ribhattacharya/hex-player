#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

#include "../include/utility.hpp"
#include "../include/graph/node.hpp"

using std::cout;
using std::string;

std::ostream &operator<<(std::ostream &os, const Pair &value)
{
    os << "(" << value.first << "," << value.second << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, const uspNode &value)
{
    os << '(';
    for (auto val : value)
        os << val << ", ";
    os << ")\n";
    return os;
}

std::ostream &operator<<(std::ostream &os, const vspNode &value)
{
    os << '[';
    for (auto val : value)
        os << val << ", ";
    os << "]\n";
    return os;
}

std::ostream &operator<<(std::ostream &os, const PlayerOrientation &value)
{
    switch (value) 
    {
        case PlayerOrientation::VERTICAL:
            os << "VERTICAL";
            break;
        case PlayerOrientation::HORIZONTAL:
            os << "HORIZONTAL";
            break;
        default:
            os << "UNKNOWN";
    }

    return os;
}

void printGraph(const Graph &g)
{
    int SIZE = g.getSize();

    std::unordered_map<PlayerType, char> symbols;
    symbols.insert(std::make_pair(PlayerType::HUMAN, 'X'));
    symbols.insert(std::make_pair(PlayerType::COMP, 'O'));
    symbols.insert(std::make_pair(PlayerType::NONE, '.'));

    cout << string(3, ' ');
    for (int col = static_cast<int>('a'), j = 0; j < SIZE; j++, col++)
    {
        cout << '|' << static_cast<char>(col) << '|';
        if (j != SIZE - 1)
            cout << string(1, ' ');
    }
    cout << "\n";

    for (int margin = 0, i = 0, row = static_cast<int>('a'); i < SIZE; i++, row++)
    {
        cout << string(margin++, ' ');
        cout << '|' << static_cast<char>(row) << '|' << string(1, ' ');
        for (int j = 0; j < SIZE; j++)
        {
            Pair idx = std::make_pair(i, j);
            PlayerType p = g.getNode(idx)->getPlayer();
            const char player_symbol = symbols[p];

            cout << player_symbol;
            if (j != SIZE - 1)
                cout << " - ";
        }
        cout << '\n';
        if (i != SIZE - 1)
        {
            cout << string(margin++ + 4, ' ');
            for (int j = 0; j < SIZE - 1; j++)
            {
                cout << "\\ / ";
            }
            cout << "\\" << '\n';
        }
    }
}