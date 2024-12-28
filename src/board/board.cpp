#include "../../include/board/Board.hpp"

#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::string;

Board::Board(int size, BridgeCheckerPtr bridgeChecker)
    : _size(size), _graph(size), _bridgeChecker(std::move(bridgeChecker)) {
}

int Board::placeMove(IntPair move, PlayerIDEnum playerId) {
    if (isValidMove(move)) {
        _graph.setNodeOccupancy(move, playerId);
        return 0;
    }

    return 1;
}

bool Board::isValidMove(IntPair move) const {
    if (move.first < 0 || move.first >= _size || move.second < 0 ||
        move.second >= _size) {
        std::cout << "Invalid move, out of bounds! Retry." << std::endl;
        return false;
    }

    if (_graph.getNodeOccupancy(move) != PlayerIDEnum::NONE) {
        std::cout << "Invalid move, cell already occupied! Retry." << std::endl;
        return false;
    }

    return true;
}

bool Board::isGameFinishedForPlayer(PlayerIDEnum playerId) const {
    if (playerId == PlayerIDEnum::PLAYER_1) {
        return _bridgeChecker->isBridgeFormed(_graph, PlayerIDEnum::PLAYER_1,
                                              DirectionEnum::HORICONTAL);
    }

    return _bridgeChecker->isBridgeFormed(_graph, PlayerIDEnum::PLAYER_2,
                                          DirectionEnum::VERTICAL);
}

int Board::getSize() const {
    return _size;
}

void Board::printBoard() const {

    std::unordered_map<PlayerIDEnum, char> symbols;
    symbols.insert(std::make_pair(PlayerIDEnum::PLAYER_1, 'X'));
    symbols.insert(std::make_pair(PlayerIDEnum::PLAYER_2, 'O'));
    symbols.insert(std::make_pair(PlayerIDEnum::NONE, '.'));

    cout << string(3, ' ');
    for (int col = 0, j = 0; j < _size; j++, col++) {
        cout << '|' << col << '|';
        if (j != _size - 1)
            cout << string(1, ' ');
    }
    cout << "\n";

    for (int margin = 0, i = 0, row = 0; i < _size; i++, row++) {
        cout << string(margin++, ' ');
        cout << '|' << row << '|' << string(1, ' ');
        for (int j = 0; j < _size; j++) {
            IntPair idx = std::make_pair(i, j);
            PlayerIDEnum p = _graph.getNodeOccupancy(idx);
            const char playerSymbol = symbols[p];

            cout << playerSymbol;
            if (j != _size - 1)
                cout << " - ";
        }
        cout << '\n';
        if (i != _size - 1) {
            cout << string(margin++ + 4, ' ');
            for (int j = 0; j < _size - 1; j++) {
                cout << "\\ / ";
            }
            cout << "\\" << '\n';
        }
    }
}