//
// Created by maxi- on 27.08.2026.
//

#include "moveGen.h"

MoveGen::MoveGen(const attack_tables& attack_tables, SlidingAttacks& sliding_attacks): attack_tables_(attack_tables), sliding_attacks_(sliding_attacks)
{

}

std::vector<Move> MoveGen::pseudo_legal_moves(Board& board)
{
    std::vector<Move> result;
    return result;
}
