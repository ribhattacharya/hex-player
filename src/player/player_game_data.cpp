#include "../../include/player/player_game_data.hpp"

PlayerGameData::PlayerGameData(PlayerOrientation orientation, uspNode starts,
                               uspNode goals)
    : _ORIENTATION(orientation), STARTS(starts), GOALS(goals) {}

PlayerGameData::PlayerGameData(const PlayerGameData &other)
    : _ORIENTATION(other._ORIENTATION), STARTS(other.STARTS), GOALS(other.GOALS) {}

PlayerOrientation PlayerGameData::getOrientation() const { return _ORIENTATION; }

uspNode PlayerGameData::getStarts() const { return STARTS; }

uspNode PlayerGameData::getGoals() const { return GOALS; }