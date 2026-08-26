//
// Created by maxi- on 22.08.2026.
//

#ifndef CHESS_ENGINE_ATTACKTABLES_H
#define CHESS_ENGINE_ATTACKTABLES_H
#include <cstdint>

class attack_tables {
    uint64_t knightAttacks[64];
    uint64_t kingAttacks[64];
    uint64_t whitePawnAttacks[64];
    uint64_t blackPawnAttacks[64];
    const uint64_t not_g_file=~0x0707070707070707;
    const uint64_t not_h_file=~0x8080808080808080;
    const uint64_t not_a_file=~0x0101010101010101;
    const uint64_t not_b_file=~0x0202020202020202;

    attack_tables() {
        for (int i = 0; i < 64; i++) {
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
            attacks |= (currentSquare & not_h_file)<<17;
            attacks |=(currentSquare & not_a_file)<<15;
            attacks|=(currentSquare & not_g_file & not_h_file)<<15;
        }
    };
};
#endif //CHESS_ENGINE_ATTACKTABLES_H
