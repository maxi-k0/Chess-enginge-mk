//
// Created by maxi- on 09.09.2026.
//

#ifndef CHESS_ENGINE_UNDOINFO_H
#define CHESS_ENGINE_UNDOINFO_H
#include <cstdint>

struct UndoInfo
{
    int previousEntPassantSquare;
    bool previousWhiteKingsideCastle;
    bool previousWhiteQueenSideCastle;
    bool previousBlackKingsideCastle;
    bool previousBlackQueenSideCastle;
    uint8_t previousForcedRemis;
};
#endif //CHESS_ENGINE_UNDOINFO_H
