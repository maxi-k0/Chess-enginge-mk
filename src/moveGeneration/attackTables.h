//
// Created by maxi- on 22.08.2026.
//

#ifndef CHESS_ENGINE_ATTACKTABLES_H
#define CHESS_ENGINE_ATTACKTABLES_H
#include <cstdint>

#include "bitboard_utils.h"

class attack_tables
{
public:
    uint64_t knightAttacks[64]{};
    uint64_t kingAttacks[64]{};
    uint64_t whitePawnAttacks[64]{};
    uint64_t blackPawnAttacks[64]{};


    attack_tables()
    {
        for (int i = 0; i < 64; i++)
        {
            //Knight attack Table initialization
            //+17 start nicht auf h
            //+15 nicht auf a
            //+10 nicht g und h
            //+6 nicht auf a und b
            //-6 nicht auf g und h
            //-10 nicht a und b
            //-15 nicht auf h
            //-17 nicht auf a
            uint64_t currentSquare = 1ULL << i;
            uint64_t attacks = 0ULL;
            attacks |= (currentSquare & not_h_file) << 17;
            attacks |= (currentSquare & not_a_file) << 15;
            attacks |= (currentSquare & not_g_file & not_h_file) << 10;
            attacks |= (currentSquare & not_a_file & not_b_file) << 6;
            attacks |= (currentSquare & not_g_file & not_h_file) >> 6;
            attacks |= (currentSquare & not_a_file & not_b_file) >> 10;
            attacks |= (currentSquare & not_h_file) >> 15;
            attacks |= (currentSquare & not_a_file) >> 17;
            knightAttacks[i] = attacks;

            //kingAttack Table initialization
            // +8
            //+9 not h file
            // +1 not h file
            // -7 not h file
            //-8
            // -9 not a file
            // -1 not a file
            // +7 not a file
            attacks = 0ULL;
            attacks |= (currentSquare) << 8;
            attacks |= (currentSquare & not_h_file) << 9;
            attacks |= (currentSquare & not_h_file) << 1;
            attacks |= (currentSquare & not_h_file) >>7;
            attacks |= (currentSquare) >> 8;
            attacks |= (currentSquare & not_a_file) >> 9;
            attacks |= (currentSquare & not_a_file) >> 1;
            attacks |= (currentSquare & not_a_file) << 7;
            kingAttacks[i] = attacks;
        }
        // WHITE PawnAttackTable initialization

        // pawns from second rank are also allowed to double push
        for (int i = 8; i < 56; ++i)
        {
            uint64_t currentSquare = 1ULL << i;
            whitePawnAttacks[i] = 0ULL | (currentSquare & not_a_file) << 7 | (currentSquare & not_h_file) << 9;
        }

        //BLACK PawnAttackTable initialization // pawns from second rank are also allowed to double push

        for (int i = 55; i > 7; --i)
        {
            uint64_t currentSquare = 1ULL << i;
            blackPawnAttacks[i] = 0ULL | (currentSquare & not_a_file) >>9 | (currentSquare & not_h_file) >> 7;
        }
    };
};
#endif //CHESS_ENGINE_ATTACKTABLES_H
