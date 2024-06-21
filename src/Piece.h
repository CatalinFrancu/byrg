#pragma once

#include "globals.h"
#include "PieceVariant.h"

class Piece {
public:
  // All distinct variants of this piece (up to 8).
  PieceVariant variants[MAX_PIECE_VARIANTS];
  int numVariants;

  bool addIfDistinct(PieceVariant var);
};
