#include "PieceVariant.h"

void PieceVariant::fromBitmap(Bitmap b, int boardSize) {
  mask = 0;
  int numBits = 0;

  for (int r = 0; b.pixels[r][0]; r++) {
    for (int c = 0; b.pixels[r][c]; c++) {
      if (b.pixels[r][c] == '*') {
        int bit = r * boardSize + c;
        mask.set(bit);
        bits[numBits++] = bit;
      }
    }
  }
}
