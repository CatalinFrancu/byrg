#pragma once

#include "globals.h"
#include "PieceVariant.h"

class Piece {
public:
  PieceVariant variants[MAX_VARIANTS];
  int size, numVariants;

  void considerBitmap(Bitmap bitmap, int boardSize);
};
