#pragma once

#include "Piece.h"

class PieceSet {
public:
  Piece pieces[NUM_PIECES];

  void precompute();
};
