#pragma once

#include "globals.h"
#include "PieceVariant.h"

class Piece {
public:
  // Keep track of the distinct variants encountered so far
  PieceVariant variants[MAX_PIECE_VARIANTS];
  int numVariants;

  bool addIfDistinct(PieceVariant var);
};
