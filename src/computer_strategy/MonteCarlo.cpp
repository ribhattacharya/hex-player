#include "computer_strategy/MonteCarlo.hpp"

#include <cassert>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

#include "Types.hpp"
#include "Utility.hpp"
#include "board/Board.hpp"

void MonteCarlo::_resetMoves(Board& simBoard, VectIntPair& movesToReset) const {
    for (auto& move : movesToReset) {
        simBoard.placeMove(move, PlayerIDEnum::NONE);
    }
}

int MonteCarlo::_evaluateWinsForMove(const Board& board,
                                     const IntPair& testMove,
                                     PlayerIDEnum& curPlayerId) const {
    int wins = 0;
    std::mt19937 gen(42);
    std::mutex winsMutex;
    std::vector<std::thread> threads;

    auto getMonteCarloWins = [&](int start, int end) {
        int localWins = 0;
        auto simBoard(board);
        simBoard.placeMove(testMove, curPlayerId);
        auto remainingMoves = _getAvailableMoves(simBoard);
        auto opponentId = _getNextPlayerID(curPlayerId);

        for (int n = start; n < end; n++) {
            std::shuffle(remainingMoves.begin(), remainingMoves.end(), gen);

            auto simCurrentPlayer = opponentId;
            for (auto& curMove : remainingMoves) {
                simBoard.placeMove(curMove, simCurrentPlayer);
                bool didCurPlayerWin =
                    simBoard.isGameFinishedForPlayer(curPlayerId);
                bool didOpponentWin =
                    simBoard.isGameFinishedForPlayer(opponentId);
                if (didCurPlayerWin) {
                    localWins++;
                    break;
                } else if (didOpponentWin) {
                    break;
                }

                simCurrentPlayer = _getNextPlayerID(simCurrentPlayer);
            }
            _resetMoves(simBoard, remainingMoves);
        }
        std::lock_guard<std::mutex> lock(winsMutex);
        wins += localWins;
    };

    int numThreads = std::thread::hardware_concurrency();
    int trialsPerThread = _NTRIALS / numThreads;
    for (int i = 0; i < numThreads; i++) {
        int start = i * trialsPerThread;
        int end = (i == numThreads - 1) ? _NTRIALS : start + trialsPerThread;
        threads.emplace_back(getMonteCarloWins, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return wins;
}

IntPair MonteCarlo::_calculateMove(const Board& board,
                                   PlayerIDEnum curPlayerId) const {
    VectIntPair movesToEvaluate = _getAvailableMoves(board);
    int maxWins = 0;
    IntPair maxWinsMove;

    for (auto& testMove : movesToEvaluate) {
        int winsForTestMove =
            _evaluateWinsForMove(board, testMove, curPlayerId);
        // std::cout << "Wins for move " << curMove << " : " << winsForCurMove
        //           << '\n';
        if (winsForTestMove > maxWins) {
            maxWins = winsForTestMove;
            maxWinsMove = testMove;
        }
    }
    std::cout << DIM << "🎯 Selected AI move: " << CYAN << maxWinsMove << RESET
              << std::endl;
    return maxWinsMove;
}

PlayerIDEnum MonteCarlo::_getNextPlayerID(PlayerIDEnum& player) const {
    assert(player != PlayerIDEnum::NONE);

    if (player == PlayerIDEnum::PLAYER_1) {
        return PlayerIDEnum::PLAYER_2;
    }
    return PlayerIDEnum::PLAYER_1;
}