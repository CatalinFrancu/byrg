#include "Piece.h"

bool Piece::addIfDistinct(PieceVariant var) {
  variants[numVariants] = var;

  // Check if the new bitset is distinct from all the others
  int i = 0;
  while (variants[i] != variants[numVariants]) {
    i++;
  }
  if (i == numVariants) {
    numVariants++;
    return true;
  } else {
    return false;
  }
}
