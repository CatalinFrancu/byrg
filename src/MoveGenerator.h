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
  bool moreMoves;
  bool shouldAppendPass;

  MoveGenerator(Board& board);

  bool isFinished();
  Move getMove();

private:
  void next();
  bool currentPieceFits();
  int getVariantId();
  int getNumPlacements();
};
