#pragma once

#include "globals.h"
#include "Board.h"
#include "Move.h"

class MoveGenerator {
public:
  Board& board;
  Cell corners[MAX_CORNERS];
  int numCorners;
  PieceSet* ps;

  int hand;
  int piece;
  int corner;
  int placement;
  bool noMoreLegal;
  bool returnedAnyMoves;

  MoveGenerator(Board& board);

  bool isFinished();
  Move getMove();

private:
  // Increment the piece / corner / placement combo.
  void next();

  // Increment to the next valid combo. Takes into account the fact that
  // numPlacements can be zero occasionally (e.g. for + pieces in the corner).
  void nextValid();

  // Increment to the next playable combo (where the variant actually fits on
  // the board).
  void nextPlayable();
  bool currentPieceFits();
  int getVariantId();
  int getNumPlacements();
};
