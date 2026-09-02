//
// Created by maxi- on 27.08.2026.
//

#include "moveGen.h"

MoveGen::MoveGen(const attack_tables& attack_tables, SlidingAttacks& sliding_attacks) : attack_tables_(attack_tables),
    sliding_attacks_(sliding_attacks)
{
}

namespace
{
    std::vector<Move> generatePawnPushes(Board& board, uint64_t pawnBitBoard)
    {

        std::vector<Move> result;
        if (board.sideToMove==1)
        {

        }
        else if (board.sideToMove==-1)
        {

        }
        else
        {
            std::cout << " Error occured. For the next move, no correct side is selected";
        }
        return result;
    }
}
std::vector<Move> MoveGen::pseudo_legal_moves(Board& board)
{
    std::vector<Move> result;
    int counter = 0;
    uint32_t square;
    int piece;
    if (board.sideToMove == 1)
    {
        uint64_t whiteOccupancyCopy = board.whiteOccupancy;
        int amountOfPieces = popCount(board.whiteOccupancy);
        while (counter < amountOfPieces)
        {
            square = popLSB(whiteOccupancyCopy);
            piece = board.lookUpTable[square];
            uint64_t attack;
            int amountOfBitsInAttack;
            switch (piece)
            {
            case W_PAWN:
                attack = attack_tables_.whitePawnAttacks[square];
                amountOfBitsInAttack = popCount(attack);
                int j = 0;
                uint32_t toTemp;
                while (j < amountOfBitsInAttack)
                {
                    toTemp = popLSB(attack);

                    Move move = {
                        .from = square,
                        .to = toTemp,
                        .piece = piece,
                        .capturedPiece = board.lookUpTable[toTemp],
                        .promotionPiece = 0,
                        false, false, false
                    };
                }
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


            default: ;
            }
            counter++;
        }
    }
    else if (board.sideToMove == -1)
    {
        uint64_t blackOccupancyCopy = board.blackOccupancy;
        int amountOfPieces = popCount(blackOccupancyCopy);
        while (counter < amountOfPieces)
        {
            square = popLSB(blackOccupancyCopy);
            piece = board.lookUpTable[square];
            uint64_t attack;
            int amountOfBitsInAttack;
            switch (piece)
            {
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
            default: ;
            }
        }
    }

    else
    {
        std::cout << " Error occured. For the next move, no correct side is selected";
    }
    return result;
}
