#include "board/board.h"
#include <iostream>
#include <cstdint>

Board::Board() {
    whitePawns = whiteKnights = whiteBishops = whiteRooks = whiteQueens = whiteKing = 0ULL;
    blackPawns = blackKnights = blackBishops = blackRooks = blackQueens = blackKing = 0ULL;

    for (int file = 8; file < 16; file++) {
        lookUpTable[file] = W_PAWN;
        lookUpTable[63 - file] = B_PAWN;
    }
    whitePawns |= 0xFF00ULL;
    blackPawns |= 0x00FF000000000000ULL;

    for (int file = 16; file < 48; file++) {
        lookUpTable[file] = EMPTY;
    }


    const int backRank[8] = {W_ROOK, W_KNIGHT, W_BISHOP, W_KING, W_QUEEN, W_BISHOP, W_KNIGHT, W_ROOK};
    for (int file = 0; file < 8; file++) {
        placePiece(file,backRank[file]);
        placePiece(56 + file,-backRank[file]);
    }

}

void Board::placePiece(int piece,int square) {
    lookUpTable[square]=piece;
    uint64_t mask = 1ULL << square;
    switch (piece) {
        case W_PAWN:
            whitePawns |= mask;
            break;
        case W_KNIGHT:
            whiteKnights |= mask;
            break;
        case W_BISHOP:
            whiteBishops |= mask;
            break;
        case W_ROOK:
            whiteRooks |= mask;
            break;
        case W_QUEEN:
            whiteQueens |= mask;
            break;
        case W_KING:
            whiteKing |= mask;
            break;
        case B_PAWN:
            blackPawns |= mask;
            break;
        case B_KNIGHT:
            blackKnights |= mask;
            break;
        case B_BISHOP:
            blackBishops |= mask;
            break;
        case B_ROOK:
            blackRooks |= mask;
            break;
        case B_QUEEN:
            blackQueens |= mask;
            break;
        case B_KING:
            blackKing |= mask;
            break;

        default:
            std::cout << "Error occured because the peace which got parsed to placePeace was not valid";


    }
}

bool Board::removePiece(int square) {
    int piece = lookUpTable[square];
    if (piece == EMPTY) {
        std::cout << " Das Feld ist schon leer ";
        return false;
    }
    lookUpTable[square]=EMPTY;
    uint64_t mask= ~(1ULL<<square);
    switch (piece) {
        case W_PAWN:
            whitePawns &= mask;
            return true;
        case W_KNIGHT:
            whiteKnights &= mask;
            return true;
        case W_BISHOP:
            whiteBishops &= mask;
            return true;
        case W_ROOK:
            whiteRooks &= mask;
            return true;
        case W_QUEEN:
            whiteQueens &= mask;
            return true;
        case W_KING:
            whiteKing &= mask;
            return true;
        case B_PAWN:
            blackPawns &= mask;
            return true;
        case B_KNIGHT:
            blackKnights &= mask;
            return true;
        case B_BISHOP:
            blackBishops &= mask;
            return true;
        case B_ROOK:
            blackRooks &= mask;
            return true;
        case B_QUEEN:
            blackQueens &= mask;
            return true;
        case B_KING:
            blackKing &= mask;
            return true;

        default:
            std::cout << "Error occured because the peace which got parsed to removePeace was not valid";
            return false;
    }

}

void Board::movePeace(int from, int to) {
    int piece = lookUpTable[from];
    removePiece(from);
    placePiece(piece,to);
}

bool Board::isValid(int from, int to) {
    int piece = lookUpTable[from];
    switch (piece) {
        case W_PAWN:

            break;
        case W_KNIGHT:

            break;
        case W_BISHOP:

            break;
        case W_ROOK:

            break;
        case W_QUEEN:

            break;
        case W_KING:

            break;
        case B_PAWN:

            break;
        case B_KNIGHT:

            break;
        case B_BISHOP:

            break;
        case B_ROOK:

            break;
        case B_QUEEN:

            break;
        case B_KING:

            break;

        default:
            std::cout << "Error occured because the peace which got parsed to placePeace was not valid";
    }
}

void Board::print(int perspective) const {
    std::cout << "Board:" << "\n";
    if (perspective == 1) {
        for (int i = 7; i >= 0; --i) {
            for (int j = 7; j >= 0; --j) {
                if (lookUpTable[i * 8 + j] >= 0) {
                    std::cout << " ";
                }
                std::cout << lookUpTable[i * 8 + j] << " ";
            }
            std::cout << "\n";
        }
    } else {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (lookUpTable[i * 8 + j] >= 0) {
                    std::cout << " ";
                }
                std::cout << lookUpTable[i * 8 + j] << " ";
            }
            std::cout << "\n";
        }
    }
}

void Board::setFromFEN(const std::string &fen) {
}
