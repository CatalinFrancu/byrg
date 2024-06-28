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
  bool anyMoves;

  MoveGenerator(Board& board);

  bool isFinished();
  Move getMove();

private:
  void next();
  void nextLegal();
  bool currentPieceFits();
  int getVariantId();
  int getNumPlacements();
};
