#include "Board.h"
#include "MoveGenerator.h"
#include <stdio.h>

/**
 * Incremental move generator. There can be on the order of 1'000 moves from
 * any given position and we hope that alpha-beta will prune much sooner that
 * that.
 **/

MoveGenerator::MoveGenerator(Board& b):
  board(b) {

  // Copy the corner list. We cannot work on the original because moves and
  // undos can reorder the list.
  numCorners = b.corners[b.stm].copy(corners);
  ps = b.pieceSet;
  hand = b.inHand[b.stm];

  if (!numCorners || !hand) {
    moreMoves = false;
  } else {
    piece = __builtin_ctz(hand);
    hand &= hand - 1;
    moreMoves = true;
  }

  corner = 0;
  placement = 0;
  shouldAppendPass = true;
}

bool MoveGenerator::isFinished() {
  return !moreMoves && !shouldAppendPass;
}

Move MoveGenerator::getMove() {
  while (moreMoves && !currentPieceFits()) {
    next();
  }

  shouldAppendPass = false;

  if (moreMoves) {
    Move result = { getVariantId(), (u8)piece };
    next();
    return result;
  } else {
    Move result;
    result.setPass();
    return result;
  }
}

// Advance to the next legal combination of piece, corner and placement. The
// piece may or may not actually fit there.
void MoveGenerator::next() {
  if (placement < getNumPlacements() - 1) {
    placement++;
  } else if (corner < numCorners - 1) {
    corner++;
    placement = 0;
  } else if (hand) {
    piece = __builtin_ctz(hand);
    hand &= hand - 1;
    corner = 0;
    placement = 0;
  } else {
    moreMoves = false;
  }
}

bool MoveGenerator::currentPieceFits() {
  int varId = getVariantId();
  Piece& var = board.pieceSet->variants[varId];
  return board.accommodates(var);
}

int MoveGenerator::getVariantId() {
  Cell c = corners[corner];
  int rank = c.rank;
  int file = c.file;
  return ps->placements[piece][rank][file][placement];
}

int MoveGenerator::getNumPlacements() {
  Cell c = corners[corner];
  int rank = c.rank;
  int file = c.file;
  return ps->numPlacements[piece][rank][file];
}
