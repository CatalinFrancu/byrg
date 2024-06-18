#include "Piece.h"

void Piece::considerBitmap(Bitmap bitmap, int boardSize) {
  size = bitmap.getSize();
  variants[numVariants].fromBitmap(bitmap, boardSize);

  // Check if the new bitset is distinct from all the others
  int i = 0;
  while (variants[i].mask != variants[numVariants].mask) {
    i++;
  }
  if (i == numVariants) {
    numVariants++;
  }
}
