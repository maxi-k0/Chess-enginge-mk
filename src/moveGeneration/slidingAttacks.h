//
// Created by maxi- on 26.08.2026.
//

#ifndef CHESS_ENGINE_SLIDINGATTACKS_H
#define CHESS_ENGINE_SLIDINGATTACKS_H
#include <cstdint>


class SlidingAttacks
{
public:
    uint64_t rayNorth[64]{};
    uint64_t rayNorthWest[64]{};
    uint64_t rayWest[64]{};
    uint64_t raySouthWest[64]{};
    uint64_t raySouth[64]{};
    uint64_t raySouthEast[64]{};
    uint64_t rayEast[64]{};
    uint64_t rayNorthEast[64]{};
    SlidingAttacks();

    uint64_t getRookAttacks(int square,uint64_t occupancy);
    // occupancy is representing the pieces of the opposing player
    uint64_t getBishopAttacks(int square,uint64_t occupancy);
    // occupancy is representing the pieces of the opposing player
    uint64_t getQueenAttacks(int square,uint64_t occupancy){return getRookAttacks(square,occupancy) | getBishopAttacks(square,occupancy);}

};


#endif //CHESS_ENGINE_SLIDINGATTACKS_H
