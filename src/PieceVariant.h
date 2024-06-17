#pragma once

#include "Bitmap.h"
#include "globals.h"

class PieceVariant {
public:
  bitset mask;               // with the piece as close as possible to bit 0
  u8 bits[MAX_PIECE_SIZE];  // indices of the set bits

  void fromBitmap(Bitmap b, int boardSize);
};
