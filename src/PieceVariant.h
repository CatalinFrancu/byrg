#pragma once

#include "Bitmap.h"
#include "Bitset.h"

class PieceVariant {
public:
  Bitset mask;              // with the piece as close as possible to bit 0
  int height, width;

  void fromBitmap(Bitmap b);
};
