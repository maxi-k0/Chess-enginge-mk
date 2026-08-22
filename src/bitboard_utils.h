//
// Created by maxi- on 22.08.2026.
//

#ifndef CHESS_ENGINE_BITBOARD_UTILS_H
#define CHESS_ENGINE_BITBOARD_UTILS_H
#include <cstdint>
#include <iostream>
inline int bitScanForward(uint64_t bitboard)
{
    if (bitboard==0)
    {
        return -1;
    }
    return __builtin_ctzll(bitboard);
}
inline int popLSB(uint64_t &bitboard)
{
    int square = bitScanForward(bitboard);
    bitboard &= bitboard-1;
    return square;
}
inline int popCount(uint64_t bitboard)
{
    return __builtin_popcountll(bitboard);
}

inline void printBitboard(uint64_t bb) {
      for (int rank = 7; rank >= 0; rank--) {
          for (int file = 0; file < 8; file++) {
              int square = rank * 8 + file;
              std::cout << ((bb >> square) & 1ULL) << " ";
          }
          std::cout << "\n";
      }
      std::cout << "\n";
  }
#endif //CHESS_ENGINE_BITBOARD_UTILS_H
