#ifndef ENUM_PLAYER
#define ENUM_PLAYER

enum class Player
{
    HUMAN,
    COMP,
    NONE
};

// std::ostream& operator<<(std::ostream& os, const Player& player)
// {
//     switch (player)
//     {
//         case Player::HUMAN:
//             os << "HUMAN";
//             break;
//         case Player::COMP:
//             os << "COMP";
//             break;
//         case Player::NONE:
//             os << "NONE";
//             break;
//         default:
//             os << "Invalid Player";
//             break;
//     }
//     return os;
// }

#endif // ENUM_PLAYER