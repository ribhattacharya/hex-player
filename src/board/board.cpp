#include "../../include/board/Board.hpp"

Board::Board(int size, BridgeCheckerPtr bridgeChecker)
    : _size(size), _graph(size), _bridgeChecker(std::move(bridgeChecker)) {
}

void Board::placeMove(IntPair move, PlayerIDEnum playerId) {
    _graph.setNodeOccupancy(move, playerId);
}

bool Board::isValidMove(IntPair move) const {
    return _graph.getNodeOccupancy(move) == PlayerIDEnum::NONE;
}

bool Board::isGameFinishedForPlayer(PlayerIDEnum playerId) const {
    if (playerId == PlayerIDEnum::PLAYER_1) {
        return _bridgeChecker->isBridgeFormed(_graph, PlayerIDEnum::PLAYER_1, DirectionEnum::HORICONTAL);
    } else {
        return _bridgeChecker->isBridgeFormed(_graph, PlayerIDEnum::PLAYER_2, DirectionEnum::VERTICAL);
    }
}