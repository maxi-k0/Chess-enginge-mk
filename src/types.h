#pragma once

// ---------------------------------------------------------------------------
// Piece constants (integers)
// ---------------------------------------------------------------------------
// Each piece is just a number. The sign tells you the color:
//   positive = White,  negative = Black,  0 = empty square
//
// Tip: abs(piece) gives you the piece type regardless of color.
//      piece > 0  means White,  piece < 0  means Black.

const int EMPTY    =  0;

const int W_PAWN   =  1;
const int W_KNIGHT =  2;
const int W_BISHOP =  3;
const int W_ROOK   =  4;
const int W_QUEEN  =  5;
const int W_KING   =  6;

const int B_PAWN   = -1;
const int B_KNIGHT = -2;
const int B_BISHOP = -3;
const int B_ROOK   = -4;
const int B_QUEEN  = -5;
const int B_KING   = -6;

// ---------------------------------------------------------------------------
// Color
// ---------------------------------------------------------------------------
// Whose turn it is to move. We keep this as a simple int too:
//   1 = White,  -1 = Black
// Multiplying a piece value by the side-to-move tells you if it's yours.
const int WHITE =  1;
const int BLACK = -1;
