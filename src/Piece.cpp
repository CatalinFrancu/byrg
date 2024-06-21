#include "Piece.h"

void Piece::considerBitmap(Bitmap bitmap) {
  size = bitmap.getSize();
  variants[numVariants].fromBitmap(bitmap);

  // Check if the new bitset is distinct from all the others
  int i = 0;
  while (variants[i].mask != variants[numVariants].mask) {
    i++;
  }
  if (i == numVariants) {
    numVariants++;
  }
}
