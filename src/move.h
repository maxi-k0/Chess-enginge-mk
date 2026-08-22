//
// Created by maxi- on 22.08.2026.
//

#ifndef CHESS_ENGINE_MOVE_H
#define CHESS_ENGINE_MOVE_H
#include <cstdint>

    struct Move
    {
        uint32_t from;
        uint32_t to;
        int piece;
        int capturedPiece;
        int promotionPiece;
        bool isEnpassant;
        bool isCastling;
        bool isDoublePawnPush;
    };

#endif //CHESS_ENGINE_MOVE_H
