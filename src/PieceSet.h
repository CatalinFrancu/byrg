#pragma once

#include "PieceVariant.h"

class PieceSet {
public:
  // Temporary array of distinct variants (up to 8).
  // Used during precompute().
  PieceVariant distinct[MAX_PIECE_VARIANTS];
  int numDistinct;

  PieceVariant variants[MAX_VARIANTS];
  int numVariants;

  // For every piece and every cell on the board, store the indices of the
  // variants that can cover that cells.
  // TODO: is u16 sufficient?
  short placements[NUM_PIECES][PADDED_BOARD_SIZE][PADDED_BOARD_SIZE]
  [MAX_PIECE_SIZE * MAX_PIECE_VARIANTS];
  int numPlacements[NUM_PIECES][PADDED_BOARD_SIZE][PADDED_BOARD_SIZE];

  void precompute();
  bool isDistinct(PieceVariant var);
  void tryAllShifts(int piece, PieceVariant var);
  void addPlacements(int piece, PieceVariant var);

  Move find(PieceVariant var);
};
