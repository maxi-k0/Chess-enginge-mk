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
    void addMoveToList(std::vector<Move>& list, uint32_t from, uint32_t to, int piece, int capturedPiece,
                       int promotionPiece, bool isEnpassant, bool isCastling, bool isDoublePawnPush)
    {
        Move move = {from, to, piece, capturedPiece, promotionPiece, isEnpassant, isCastling, isDoublePawnPush};
        list.push_back(move);
    }

    // Walks every set bit in an attacks-bitboard and adds one Move per target square.
    void addAttacksToMoveList(uint64_t attacks, uint32_t from, int piece, const Board& board, std::vector<Move>& list)
    {
        while (attacks)
        {
            const uint32_t to = popLSB(attacks);
            addMoveToList(list, from, to, piece, board.lookUpTable[to], 0, false, false, false);
        }
    }

    void generatePawnPushes(const Board& board, std::vector<Move>& list)
    {
        if (board.sideToMove == WHITE)
        {
            uint64_t pawnCopy = board.whitePawns;
            const int amountOfPawns = popCount(pawnCopy);
            int counter = 0;
            while (counter < amountOfPawns)
            {
                uint32_t square = popLSB(pawnCopy);
                if (board.lookUpTable[square + 8] == EMPTY)
                {
                    if ((square + 8) > 55)
                        //checks if the pawn moves to the last rank, if so generates all possible promotions
                    {
                        addMoveToList(list, square, square + 8, W_PAWN, 0, W_QUEEN, false, false, false);
                        addMoveToList(list, square, square + 8, W_PAWN, 0, W_KNIGHT, false, false, false);
                        addMoveToList(list, square, square + 8, W_PAWN, 0, W_ROOK, false, false, false);
                        addMoveToList(list, square, square + 8, W_PAWN, 0, W_BISHOP, false, false, false);
                    }
                    else{
                        addMoveToList(list, square, square + 8, W_PAWN, 0, 0, false, false, false);
                    }

                    if (square > 7 && square < 16 && board.lookUpTable[square + 16] == EMPTY)
                        // checks if the pawn is still allowed to double push
                    {
                        addMoveToList(list, square, square + 16, W_PAWN, 0, 0, false, false, true);
                    }
                    counter++;
                }
            }
        }
        else if (board.sideToMove == BLACK)
        {
            uint64_t pawnCopy = board.blackPawns;
            const int amountOfPawns = popCount(pawnCopy);
            int counter = 0;
            while (counter < amountOfPawns)
            {
                uint32_t square = popLSB(pawnCopy);
                if (board.lookUpTable[square - 8] == EMPTY)
                {
                    if ((square - 8) < 8)
                        //checks if the pawn moves to the last rank, if so generates all possible promotions
                    {
                        addMoveToList(list, square, square - 8, B_PAWN, 0, B_QUEEN, false, false, false);
                        addMoveToList(list, square, square - 8, B_PAWN, 0, B_KNIGHT, false, false, false);
                        addMoveToList(list, square, square - 8, B_PAWN, 0, B_ROOK, false, false, false);
                        addMoveToList(list, square, square - 8, B_PAWN, 0, B_BISHOP, false, false, false);
                    }
                    else
                    {
                        addMoveToList(list, square, square - 8, B_PAWN, 0, 0, false, false, false);
                    }

                    if (square > 47 && square < 56 && board.lookUpTable[square - 16] == EMPTY)
                        // checks if the pawn is still allowed to double push
                    {
                        addMoveToList(list, square, square - 16, B_PAWN, 0, 0, false, false, true);
                    }
                    counter++;
                }
            }
        }
        else
        {
            std::cout << " Error occurred :generatePawnPushes. For the next move, no correct side is selected";
        }
    }
}

bool MoveGen::isSquareAttacked(const Board& board, int square, const int side) const
{
    uint64_t bit = 1ULL << square;
    uint64_t attack = 0ULL;
    int counter = 0;
    if (side == WHITE)
    {
        uint64_t occupancy = board.blackOccupancy;
        const int amountOfPieces = popCount(occupancy);
        while (counter < amountOfPieces)
        {
            square = popLSB(occupancy);
            switch (board.lookUpTable[square])
            {
            case B_PAWN:
                attack |= attack_tables_.blackPawnAttacks[square];
                break;
            case B_KNIGHT:
                attack |= attack_tables_.knightAttacks[square];
                break;
            case B_BISHOP:
                attack |= sliding_attacks_.getBishopAttacks(square, board.whiteOccupancy | board.blackOccupancy);
                break;
            case B_ROOK:
                attack |= sliding_attacks_.getRookAttacks(square, board.whiteOccupancy | board.blackOccupancy);
                break;
            case B_QUEEN:
                attack |= sliding_attacks_.getQueenAttacks(square, board.whiteOccupancy | board.blackOccupancy);
                break;
            case B_KING:
                attack |= attack_tables_.kingAttacks[square];
                break;
            default: std::cout << "The number of the piece cant be evaluated. Error is occurred in: isSquareAttacked";
            }
            counter++;
        }
    }
    else if (side == BLACK)
    {
        uint64_t occupancy = board.whiteOccupancy;
        const int amountOfPieces = popCount(occupancy);
        while (counter < amountOfPieces)
        {
            square = popLSB(occupancy);
            switch (board.lookUpTable[square])
            {
            case W_PAWN:
                attack |= attack_tables_.whitePawnAttacks[square];
                break;
            case W_KNIGHT:
                attack |= attack_tables_.knightAttacks[square];
                break;
            case W_BISHOP:
                attack |= sliding_attacks_.getBishopAttacks(square, board.blackOccupancy | board.whiteOccupancy);
                break;
            case W_ROOK:
                attack |= sliding_attacks_.getRookAttacks(square, board.blackOccupancy | board.whiteOccupancy);
                break;
            case W_QUEEN:
                attack |= sliding_attacks_.getQueenAttacks(square, board.blackOccupancy | board.whiteOccupancy);
                break;
            case W_KING:
                attack |= attack_tables_.kingAttacks[square];
                break;
            default: std::cout << "The number of the piece cant be evaluated. Error occurred in: isSquareAttacked";
            }
            counter++;
        }
    }
    else
    {
        std::cout << "The value is the side can't be evaluated. Error occurred in:isSquareAttacked";
    }
    return (bit & attack) != 0;
}

std::vector<Move> MoveGen::legal_moves(const Board& board)
{

}

std::vector<Move> MoveGen::pseudo_legal_moves(const Board& board)
{
    std::vector<Move> result;
    int counter = 0;
    uint32_t square;
    int piece;
    generatePawnPushes(board, result);
    if (board.sideToMove == 1)
    {
        uint64_t whiteOccupancyCopy = board.whiteOccupancy;
        int amountOfPieces = popCount(board.whiteOccupancy);
        while (counter < amountOfPieces)
        {
            square = popLSB(whiteOccupancyCopy);
            piece = board.lookUpTable[square];
            uint64_t attack;
            switch (piece)
            {
            case W_PAWN:
                {
                    // // man koennte hier die pawnPushes in einem seperaten Thread ausführen diesen Thread die Referenz zu unserer Liste geben und dann mit einem mutex sicherstellen dass die Liste
                    // //ordnungsgemäß verändert wird. Das ist ein Vorschlag für eine Optimierung fuer spaeter
                    attack = attack_tables_.whitePawnAttacks[square];
                    const int amountOfBitsInAttack = popCount(attack);
                    int j = 0;
                    while (j < amountOfBitsInAttack)
                    {
                        const uint32_t toTemp = popLSB(attack);
                        if (const int capturedPiece=board.lookUpTable[toTemp]; toTemp>47&& capturedPiece<0)
                        {
                            addMoveToList(result, square, toTemp, W_PAWN, capturedPiece, W_QUEEN, false, false, false);
                            addMoveToList(result, square, toTemp, W_PAWN, capturedPiece, W_KNIGHT, false, false, false);
                            addMoveToList(result, square, toTemp, W_PAWN, capturedPiece, W_ROOK, false, false, false);
                            addMoveToList(result, square, toTemp, W_PAWN, capturedPiece, W_BISHOP, false, false, false);
                        }
                        else if (capturedPiece<0)
                        {
                            addMoveToList(result, square, toTemp, W_PAWN, capturedPiece, 0, false, false, false);
                        }
                        else if (toTemp == board.entPassantSquare)
                        {
                            addMoveToList(result, square, toTemp, W_PAWN, B_PAWN, 0, true, false, false);
                        }
                        j++;
                    }
                }
                break;
            case W_KNIGHT:
                addAttacksToMoveList(attack_tables_.knightAttacks[square] & ~board.whiteOccupancy, square, W_KNIGHT, board, result);
                break;
            case W_BISHOP:
                addAttacksToMoveList(sliding_attacks_.getBishopAttacks(square, board.whiteOccupancy | board.blackOccupancy) & ~board.whiteOccupancy, square, W_BISHOP, board, result);
                break;
            case W_ROOK:
                addAttacksToMoveList(sliding_attacks_.getRookAttacks(square, board.whiteOccupancy | board.blackOccupancy) & ~board.whiteOccupancy, square, W_ROOK, board, result);
                break;
            case W_QUEEN:
                addAttacksToMoveList(sliding_attacks_.getQueenAttacks(square, board.whiteOccupancy | board.blackOccupancy) & ~board.whiteOccupancy, square, W_QUEEN, board, result);
                break;
            case W_KING:
                {
                    addAttacksToMoveList(attack_tables_.kingAttacks[square] & ~board.whiteOccupancy, square, W_KING, board, result);
                    const uint64_t occupancy = board.whiteOccupancy | board.blackOccupancy;
                    if (board.whiteKingsideCastle && (occupancy & 0x60ULL) == 0){
                        addMoveToList(result,square,square+2,W_KING,EMPTY,0,false,true,false);
                    }
                    if (board.whiteQueenSideCastle && (occupancy & 0x0EULL) == 0)
                    {
                        addMoveToList(result,square,square-2,W_KING,EMPTY,0,false,true,false);
                    }
                }
                break;
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
            switch (piece)
            {
            case B_PAWN:
                {
                    attack = attack_tables_.blackPawnAttacks[square];
                    const int amountOfBitsInAttack = popCount(attack);
                    int j = 0;
                    while (j < amountOfBitsInAttack)
                    {
                        const uint32_t toTemp = popLSB(attack);
                        if (const int capturedPiece=board.lookUpTable[toTemp]; toTemp<8&& capturedPiece>0)
                        {
                            addMoveToList(result, square, toTemp, B_PAWN, capturedPiece, B_QUEEN, false, false, false);
                            addMoveToList(result, square, toTemp, B_PAWN, capturedPiece, B_KNIGHT, false, false, false);
                            addMoveToList(result, square, toTemp, B_PAWN, capturedPiece, B_ROOK, false, false, false);
                            addMoveToList(result, square, toTemp, B_PAWN, capturedPiece, B_BISHOP, false, false, false);
                        }
                        else if (capturedPiece>0)
                        {
                            addMoveToList(result, square, toTemp, B_PAWN, capturedPiece, 0, false, false, false);
                        }
                        j++;
                    }
                }

                break;
            case B_KNIGHT:
                addAttacksToMoveList(attack_tables_.knightAttacks[square] & ~board.blackOccupancy,square,B_KNIGHT,board,result);
                break;
            case B_BISHOP:
                addAttacksToMoveList(sliding_attacks_.getBishopAttacks(square,(board.blackOccupancy |board.whiteOccupancy)) & ~board.blackOccupancy,square,B_BISHOP,board,result);
                break;
            case B_ROOK:
                addAttacksToMoveList(sliding_attacks_.getRookAttacks(square,(board.blackOccupancy |board.whiteOccupancy)) & ~board.blackOccupancy,square,B_ROOK,board,result);

                break;
            case B_QUEEN:
                addAttacksToMoveList(sliding_attacks_.getQueenAttacks(square,(board.blackOccupancy |board.whiteOccupancy)) & ~board.blackOccupancy,square,B_QUEEN,board,result);
                break;
            case B_KING:
                {
                    addAttacksToMoveList(attack_tables_.kingAttacks[square] & ~board.blackOccupancy, square, B_KING, board, result);
                    const uint64_t occupancy = board.whiteOccupancy | board.blackOccupancy;
                    if (board.blackKingsideCastle && (occupancy & 0x6000000000000000ULL) == 0){
                        addMoveToList(result,square,square+2,B_KING,EMPTY,0,false,true,false);
                    }
                    if (board.blackQueenSideCastle && (occupancy & 0x0E00000000000000ULL) == 0)
                    {
                        addMoveToList(result,square,square-2,B_KING,EMPTY,0,false,true,false);
                    }
                }
                break;
            default: ;
            }
            counter++;
        }
    }

    else
    {
        std::cout << " Error occurred. For the next move, no correct side is selected";
    }
    return result;
}