#pragma once

#include "Piece.h"

class PieceSet {
public:
  // Temporary array of distinct variants (up to 8).
  // Used during precompute().
  Piece distinct[MAX_PIECE_VARIANTS];
  int numDistinct;

  Piece variants[MAX_VARIANTS];
  int numVariants;

  // For every piece and every cell on the board, store the indices of the
  // variants that can cover that cells.
  // TODO: is u16 sufficient?
  short placements[NUM_PIECES][PADDED_BOARD_SIZE][PADDED_BOARD_SIZE]
  [MAX_PIECE_SIZE * MAX_PIECE_VARIANTS];
  int numPlacements[NUM_PIECES][PADDED_BOARD_SIZE][PADDED_BOARD_SIZE];

  void precompute();
  bool isDistinct(Piece p);
  void tryAllShifts(int piece, Piece var);
  void addPlacements(int piece, Piece var);

  Move find(Piece var);
};
