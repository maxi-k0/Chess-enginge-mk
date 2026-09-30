#include <gtest/gtest.h>
#include "board/board.h"
#include "types.h"

TEST(BoardInitialization, PawnBitboardsAreCorrect) {
    Board board;
    EXPECT_EQ(board.whitePawns, 0x000000000000FF00ULL);
    EXPECT_EQ(board.blackPawns, 0x00FF000000000000ULL);
}

TEST(BoardInitialization, WhiteBackRankPiecesAreCorrect) {
    Board board;
    EXPECT_EQ(board.lookUpTable[0], W_ROOK);
    EXPECT_EQ(board.lookUpTable[1], W_KNIGHT);
    EXPECT_EQ(board.lookUpTable[2], W_BISHOP);
    EXPECT_EQ(board.lookUpTable[3], W_QUEEN);
    EXPECT_EQ(board.lookUpTable[4], W_KING);
    EXPECT_EQ(board.lookUpTable[5], W_BISHOP);
    EXPECT_EQ(board.lookUpTable[6], W_KNIGHT);
    EXPECT_EQ(board.lookUpTable[7], W_ROOK);
}

TEST(BoardInitialization, BlackBackRankPiecesAreCorrect) {
    Board board;
    EXPECT_EQ(board.lookUpTable[56], B_ROOK);
    EXPECT_EQ(board.lookUpTable[57], B_KNIGHT);
    EXPECT_EQ(board.lookUpTable[58], B_BISHOP);
    EXPECT_EQ(board.lookUpTable[59], B_QUEEN);
    EXPECT_EQ(board.lookUpTable[60], B_KING);
    EXPECT_EQ(board.lookUpTable[61], B_BISHOP);
    EXPECT_EQ(board.lookUpTable[62], B_KNIGHT);
    EXPECT_EQ(board.lookUpTable[63], B_ROOK);
}

TEST(BoardInitialization, MiddleRanksAreEmpty) {
    Board board;
    for (int square = 16; square < 48; square++) {
        EXPECT_EQ(board.lookUpTable[square], EMPTY) << "square " << square << " should be empty";
    }
}

TEST(BoardInitialization, PieceBitboardsMatchStartingPosition) {
    Board board;
    EXPECT_EQ(board.whiteRooks,   (1ULL << 0) | (1ULL << 7));
    EXPECT_EQ(board.whiteKnights, (1ULL << 1) | (1ULL << 6));
    EXPECT_EQ(board.whiteBishops, (1ULL << 2) | (1ULL << 5));
    EXPECT_EQ(board.whiteQueens,  1ULL << 3);
    EXPECT_EQ(board.whiteKing,    1ULL << 4);

    EXPECT_EQ(board.blackRooks,   (1ULL << 56) | (1ULL << 63));
    EXPECT_EQ(board.blackKnights, (1ULL << 57) | (1ULL << 62));
    EXPECT_EQ(board.blackBishops, (1ULL << 58) | (1ULL << 61));
    EXPECT_EQ(board.blackQueens,  1ULL << 59);
    EXPECT_EQ(board.blackKing,    1ULL << 60);
}

TEST(BoardInitialization, OccupancyBitboardsMatchAllPieces) {
    Board board;
    uint64_t expectedWhite = board.whitePawns | board.whiteKnights | board.whiteBishops
                            | board.whiteRooks | board.whiteQueens | board.whiteKing;
    uint64_t expectedBlack = board.blackPawns | board.blackKnights | board.blackBishops
                            | board.blackRooks | board.blackQueens | board.blackKing;
    EXPECT_EQ(board.whiteOccupancy, expectedWhite);
    EXPECT_EQ(board.blackOccupancy, expectedBlack);
}

TEST(BoardInitialization, GameStateDefaultsAreCorrect) {
    Board board;
    EXPECT_EQ(board.sideToMove, WHITE);
    EXPECT_EQ(board.entPassantSquare, -1);
    EXPECT_TRUE(board.whiteKingsideCastle);
    EXPECT_TRUE(board.whiteQueenSideCastle);
    EXPECT_TRUE(board.blackKingsideCastle);
    EXPECT_TRUE(board.blackQueenSideCastle);
}
