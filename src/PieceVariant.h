#pragma once

#include "Bitmap.h"
#include "Bitset.h"

class PieceVariant {
public:
  Bitset mask;              // with the piece as close as possible to bit 0
  u8 bits[MAX_PIECE_SIZE];  // indices of the set bits
  int height, width;

  void fromBitmap(Bitmap b, int boardSize);
};
