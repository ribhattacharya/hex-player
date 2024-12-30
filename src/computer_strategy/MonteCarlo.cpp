#include "computer_strategy/MonteCarlo.hpp"

#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "Utility.hpp"

void MonteCarlo::_resetMoves(Board& simBoard,
                             VectIntPair& availableMoves) const {
    for (auto& move : availableMoves) {
        simBoard.placeMove(move, PlayerIDEnum::NONE);
    }
}
bool MonteCarlo::_didPlayerWin(Board& simBoard, VectIntPair& simAvailableMoves,
                              PlayerIDEnum& curPlayerId) const {
    PlayerIDEnum otherPlayerId = _getNextPlayerID(curPlayerId);
    IntPair nextMove;
    for (int j = 0; j < simAvailableMoves.size();) {
        nextMove = simAvailableMoves[j++];
        simBoard.placeMove(nextMove, otherPlayerId);
        if (simBoard.isGameFinishedForPlayer(otherPlayerId) ||
            j == simAvailableMoves.size()) {
            return false;
        }

        nextMove = simAvailableMoves[j++];
        simBoard.placeMove(nextMove, curPlayerId);
        if (simBoard.isGameFinishedForPlayer(curPlayerId)) {
            return true;
        }
    }

    return false;
}
int MonteCarlo::_getWinsFromAllTrials(Board& simBoard,
                                      VectIntPair& simAvailableMoves,
                                      PlayerIDEnum& curPlayerId,
                                      std::mt19937& gen) const {
    int wins = 0;
    for (int n = 0; n < _NTRIALS; n++) {
        std::shuffle(simAvailableMoves.begin(), simAvailableMoves.end(), gen);
        if (_didPlayerWin(simBoard, simAvailableMoves, curPlayerId)) {
            wins++;
        }
        _resetMoves(simBoard, simAvailableMoves);
    }

    return wins;
}
IntPair MonteCarlo::_calculateMove(const Board& board,
                                   PlayerIDEnum curPlayerId) const {
    VectIntPair availableMoves = _getAvailableMoves(board);
    VectIntPair simAvailableMoves;
    Board simBoard(board);
    std::mt19937 gen(42);

    int maxWins = 0, winsForTestMove = 0;
    IntPair maxWinsMove, testMove;

    for (int i = 0; i < availableMoves.size(); i++) {
        testMove = availableMoves[i];
        winsForTestMove = 0;

        // Place test move for current player
        simAvailableMoves = availableMoves;
        simBoard.placeMove(testMove, curPlayerId);
        simAvailableMoves.erase(simAvailableMoves.begin() + i);

        winsForTestMove = _getWinsFromAllTrials(simBoard, simAvailableMoves,
                                                curPlayerId, gen);
        // std::cout << "Wins for move " << curMove << " : " << winsForCurMove
        //           << '\n';
        if (winsForTestMove > maxWins) {
            maxWins = winsForTestMove;
            maxWinsMove = testMove;
        }
    }
    std::cout << "\nSelected AI move: " << maxWinsMove << std::endl;
    return maxWinsMove;
}

PlayerIDEnum MonteCarlo::_getNextPlayerID(PlayerIDEnum& player) const {

    assert(player != PlayerIDEnum::NONE);
    
    if (player == PlayerIDEnum::PLAYER_1) {
        return PlayerIDEnum::PLAYER_2;
    }
    return PlayerIDEnum::PLAYER_1;
}

VectIntPair MonteCarlo::_getAvailableMoves(const Board& board) const {
    VectIntPair availableMoves;
    for (int i = 0; i < board.getSize(); i++) {
        for (int j = 0; j < board.getSize(); j++) {
            if (board.isValidMove({i, j})) {
                availableMoves.push_back({i, j});
            }
        }
    }
    return availableMoves;
}