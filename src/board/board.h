#pragma once

#include <cstdint>

#include "types.h"
#include <string>

// ---------------------------------------------------------------------------
// Board
// ---------------------------------------------------------------------------
// Holds the current position as a plain 8×8 grid of integers.
// board[rank][file]  — rank 0 = rank-1 (White's side), rank 7 = rank-8.
//
// Each cell is one of the piece constants from types.h:
//   0 = empty,  positive = White piece,  negative = Black piece.
class Board {
public:
    //bitboards for pieces
    int entPassantSquare;
    bool whiteKingsideCastle,whiteQueenSideCastle,blackKingsideCastle,blackQueenSideCastle;
    uint8_t forcedRemis;
    uint64_t whitePawns, whiteKnights, whiteBishops, whiteRooks, whiteQueens, whiteKing;
    uint64_t blackPawns, blackKnights, blackBishops, blackRooks, blackQueens, blackKing;
    uint64_t blackOccupancy, whiteOccupancy;
    int lookUpTable[64];

    // Whose turn it is: WHITE (1) or BLACK (-1).
    int sideToMove = WHITE;

    // Sets up the standard chess starting position.
    Board();

    // Prints the board to the console so you can see what's going on.
    void print(int perspective) const;

    // Sets the board from a FEN string (implement this in Week 1).
    // Example FEN: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    void setFromFEN(const std::string& fen);

    void placePiece(int piece,int square);

    bool removePiece(int square);

    void movePeace(int from, int to);
    bool isValid(int from, int to);
};
