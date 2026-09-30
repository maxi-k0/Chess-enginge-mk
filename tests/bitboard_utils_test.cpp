#include <gtest/gtest.h>
#include "bitboard_utils.h"

TEST(BitboardUtils, BitScanForwardReturnsMinusOneForEmpty) {
    EXPECT_EQ(bitScanForward(0ULL), -1);
}

TEST(BitboardUtils, BitScanForwardFindsLowestBit) {
    EXPECT_EQ(bitScanForward(0b1010ULL), 1);
}
