#pragma once

#include "Piece.h"
#include "PieceVariant.h"

class PieceSet {
public:
  PieceVariant variants[MAX_VARIANTS];
  int numVariants;
  Piece pieces[NUM_PIECES];

  // For every piece and every cell on the board, store the indices of the
  // variants that can cover that cells.
  // TODO: is u16 sufficient?
  int placements[NUM_PIECES][PADDED_BOARD_SIZE][PADDED_BOARD_SIZE]
  [MAX_PIECE_SIZE * MAX_PIECE_VARIANTS];
  int numPlacements[NUM_PIECES][PADDED_BOARD_SIZE][PADDED_BOARD_SIZE];

  void precompute();
  void tryAllShifts(int piece, PieceVariant var);
  void addPlacements(int piece, PieceVariant var);

  Move find(PieceVariant var);
};
