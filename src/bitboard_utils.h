//
// Created by maxi- on 22.08.2026.
//

#ifndef CHESS_ENGINE_BITBOARD_UTILS_H
#define CHESS_ENGINE_BITBOARD_UTILS_H
#include <cstdint>
#include <iostream>
inline constexpr uint64_t not_g_file = ~0x0707070707070707;
inline constexpr uint64_t not_h_file = ~0x8080808080808080;
inline constexpr uint64_t not_a_file = ~0x0101010101010101;
inline constexpr uint64_t not_b_file = ~0x0202020202020202;


// findet niedrigswertige gesetzte Bit (LSB least significant bit) returned feldnummer
inline int bitScanForward(uint64_t bitboard)
{
    if (bitboard==0) // check weil __builtin_ctzll(0) undefiniert ist
    {
        return -1;
    }
    return __builtin_ctzll(bitboard); // zählt wie viele Nullen von rechts kommen bis die erste 1 auftaucht
}
//findet das höchsgesetze bit (MSB most significant bit) returned feldnummer
inline int bitScanReversed( uint64_t bitboard)
{
    if (bitboard == 0)
    {
        return -1;
    }
    return 63-__builtin_clzll(bitboard);
}
inline int popLSB(uint64_t &bitboard) //findet das niedrigste gesetzte Bit und löscht es gleichzeitig aus dem übergebenen Bitboard
{
    int square = bitScanForward(bitboard);
    bitboard &= bitboard-1;
    return square;
}
inline int popCount(uint64_t bitboard) // zählt wie viele Bits insgesamt gesetzt sin
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
