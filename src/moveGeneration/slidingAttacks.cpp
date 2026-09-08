//
// Created by maxi- on 26.08.2026.
//

#include "slidingAttacks.h"
#include "bitboard_utils.h"

namespace
{
    // attackIn Direction takes the rays and cuts them at the blocker bit. The Occupancy is representing the pieces of the enemy.
    uint64_t attackInDirection(int square, uint64_t ray[], uint64_t occupancy, bool forwardDirection)
    {
        uint64_t blocker = ray[square] & occupancy;
        if (blocker == 0)
        {
            return ray[square];
        }
        int blockerBit;
        if (forwardDirection)
        {
            blockerBit = bitScanForward(blocker);
        }
        else
        {
            blockerBit = bitScanReversed(blocker);
        }
        return ray[square] & ~ray[blockerBit];
    }
}

SlidingAttacks::SlidingAttacks()
{
    // Initalizing the ray Arrays for the lookUp of rays
    for (int i = 0; i < 64; ++i)
    {
        uint64_t attacksNorth = 0ULL;
        uint64_t attacksNorthWest = 0ULL;
        uint64_t attacksWest = 0ULL;
        uint64_t attacksSouthWest = 0ULL;
        uint64_t attacksSouth = 0ULL;
        uint64_t attacksSouthEast = 0ULL;
        uint64_t attacksEast = 0ULL;
        uint64_t attacksNorthEast = 0ULL;

        uint64_t currentNorth = 1ULL << i;
        uint64_t currentNorthEast = 1ULL << i;
        uint64_t currentEast = 1ULL << i;
        uint64_t currentSouthEast = 1ULL << i;
        uint64_t currentSouth = 1ULL << i;
        uint64_t currentSouthWest = 1ULL << i;
        uint64_t currentWest = 1ULL << i;
        uint64_t currentNorthWest = 1ULL << i;
        for (int i1 = 0; i1 < 7; ++i1)
        {
            currentNorth = currentNorth << 8;
            attacksNorth |= currentNorth;

            currentNorthEast = (currentNorthEast & not_h_file) << 9;
            attacksNorthEast |= currentNorthEast;

            currentEast = (currentEast & not_h_file) << 1;
            attacksEast |= currentEast;

            currentSouthEast = (currentSouthEast & not_h_file) >> 7;
            attacksSouthEast |= currentSouthEast;

            currentSouth = currentSouth >> 8;
            attacksSouth |= currentSouth;

            currentSouthWest = (currentSouthWest & not_a_file) >> 9;
            attacksSouthWest |= currentSouthWest;

            currentWest = (currentWest & not_a_file) >> 1;
            attacksWest |= currentWest;

            currentNorthWest = (currentNorthWest & not_a_file) << 7;
            attacksNorthWest |= currentNorthWest;
        }
        rayNorth[i]=attacksNorth;
        rayNorthEast[i]=attacksNorthEast;
        rayEast[i]=attacksEast;
        raySouthEast[i]=attacksSouthEast;
        raySouth[i]=attacksSouth;
        raySouthWest[i]=attacksSouthWest;
        rayWest[i]=attacksWest;
        rayNorthWest[i]=attacksNorthWest;
    }
}
// occupancy is representing the pieces of the opposing player
uint64_t SlidingAttacks::getRookAttacks(int square, uint64_t occupancy)
{
    uint64_t rookAttack = 0ULL;
    rookAttack = attackInDirection(square, rayNorth, occupancy, true)
        | attackInDirection(square, rayWest, occupancy, false)
        | attackInDirection(square, raySouth, occupancy, false)
        | attackInDirection(square, rayEast, occupancy, true);
    return rookAttack;
}
// occupancy is representing the pieces of the opposing player
uint64_t SlidingAttacks::getBishopAttacks(int square, uint64_t occupancy)
{
    uint64_t bishopAttack = 0ULL;
    bishopAttack = attackInDirection(square, rayNorthEast, occupancy, true)
        | attackInDirection(square, raySouthEast, occupancy, false)
        | attackInDirection(square, raySouthWest, occupancy, false)
        | attackInDirection(square, rayNorthWest, occupancy, true);
    return bishopAttack;
}
