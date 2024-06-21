#pragma once

#include "Piece.h"

class PieceSet {
public:
  // For every piece and every bit of the board, store the shifted pieces that
  // can cover that bit.
  Bitset shiftedMasks[NUM_PIECES][NUM_BITS][MAX_PIECE_SIZE * MAX_VARIANTS];
  u8 numShifts[NUM_PIECES][NUM_BITS];

  Piece pieces[NUM_PIECES];

  void precompute();

private:
  void tryAllShifts(int piece, int var);

};
