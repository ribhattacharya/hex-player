#include "../../include/computer_strategy/MonteCarlo.hpp"

#include <iostream>
#include <random>
#include <vector>

#include "../../include/Utility.hpp"

// TODO: revert changes to node instead of reconstructing the board

IntPair MonteCarlo::_calculateMove(const Board& board,
                                   PlayerIDEnum curPlayerId) const {
    VectIntPair availableMoves = _getAvailableMoves(board);
    VectIntPair simAvailableMoves = availableMoves;
    Board simBoard(board);
    PlayerIDEnum otherPlayerId = _getOtherPlayerID(curPlayerId);
    int maxWins = 0;
    IntPair maxWinsMove;
    std::mt19937 gen(42);

    for (int i = 0; i < availableMoves.size(); i++) {
        IntPair testMove = availableMoves[i];
        int winsForTestMove = 0;

        simAvailableMoves = availableMoves;
        simBoard.placeMove(testMove, curPlayerId);
        simAvailableMoves.erase(simAvailableMoves.begin() + i);

        PlayerIDEnum nextPlayerId = _getOtherPlayerID(curPlayerId);

        // int randIdx;
        // IntPair nextMove;

        // simBoard = board;
        // std::cout << "Simulating move " << curMove << " for player "
        //           << int(curPlayerId) << " Board : " << &board
        //           << ", SimBoard : " << &simBoard << '\n';

        for (int n = 0; n < _NTRIALS; n++) {
            std::shuffle(simAvailableMoves.begin(), simAvailableMoves.end(), gen);
            for (auto& nextMove : simAvailableMoves) {
                // std::uniform_int_distribution<int> dis(
                //     0, simAvailableMoves.size() - 1);

                // randIdx = dis(gen);
                // nextMove = simAvailableMoves[randIdx];
                // simAvailableMoves.erase(simAvailableMoves.begin() + randIdx);
                simBoard.placeMove(nextMove, nextPlayerId);
                nextPlayerId = _getOtherPlayerID(nextPlayerId);

                if (simBoard.isGameFinishedForPlayer(curPlayerId)) {
                    winsForTestMove++;
                    break;
                } else if (simBoard.isGameFinishedForPlayer(otherPlayerId)) {
                    break;
                }
            }
            // Reset the board for the next simulation
            for (auto& move : availableMoves) {
                simBoard.placeMove(move, PlayerIDEnum::NONE);
            }
            simBoard.placeMove(testMove, curPlayerId);
        }
        // std::cout << "Wins for move " << curMove << " : " << winsForCurMove
        //           << '\n';
        if (winsForTestMove > maxWins) {
            maxWins = winsForTestMove;
            maxWinsMove = testMove;
        }
    }
    std::cout << "\nSelected AI move: " << maxWinsMove;
    return maxWinsMove;
}

PlayerIDEnum MonteCarlo::_getOtherPlayerID(PlayerIDEnum& player) const {
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