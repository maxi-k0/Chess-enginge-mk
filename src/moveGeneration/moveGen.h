//
// Created by maxi- on 27.08.2026.
//

#ifndef CHESS_ENGINE_MOVEGEN_H
#define CHESS_ENGINE_MOVEGEN_H
#include <vector>

#include "attackTables.h"
#include "move.h"
#include "slidingAttacks.h"
#include "board/board.h"


class MoveGen
{
public:
    MoveGen(const attack_tables& attack_tables, SlidingAttacks& sliding_attacks);
    std::vector<Move> pseudo_legal_moves(const Board& board);
    std::vector<Move> legal_moves(const Board& board);

    bool isSquareAttacked(const Board& board,int square, int side) const;
private:
    const attack_tables& attack_tables_;
    SlidingAttacks& sliding_attacks_;
};


#endif //CHESS_ENGINE_MOVEGEN_H
