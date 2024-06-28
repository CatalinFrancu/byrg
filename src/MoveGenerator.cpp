#include "Board.h"
#include "MoveGenerator.h"
#include <stdio.h>

MoveGenerator::MoveGenerator(Board& b):
  board(b) {
  numMoves = 0;
}

void MoveGenerator::run() {
  tryEveryPiece();
  passIfNoMoves();
}

void MoveGenerator::tryEveryPiece() {
  int hand = board.inHand[board.stm];
  while (hand) {
    int piece = __builtin_ctz(hand);
    tryEveryCorner(piece);
    hand &= hand - 1;
  }
}

void MoveGenerator::tryEveryCorner(int piece) {
  CornerList& cl = board.corners[board.stm];
  for (int i = 0; i < cl.size; i++) {
    tryEveryShape(piece, cl.list[i]);
  }
}

void MoveGenerator::tryEveryShape(int piece, Cell corner) {
  int rank = corner.rank;
  int file = corner.file;
  PieceSet* ps = board.pieceSet;
  int n = ps->numPlacements[piece][rank][file];
  for (int i = 0; i < n; i++) {
    int varId = ps->placements[piece][rank][file][i];
    tryShape(piece, varId);
  }
}

void MoveGenerator::tryShape(u8 piece, int varId) {
  Piece& var = board.pieceSet->variants[varId];
  if (board.accommodates(var)) {
    moves[numMoves++] = { varId, piece };
  }
}

void MoveGenerator::passIfNoMoves() {
  if (!numMoves) {
    moves[0].setPass();
    numMoves = 1;
  }
}
