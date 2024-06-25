#include "Board.h"
#include "MoveGenerator.h"
#include <stdio.h>

MoveGenerator::MoveGenerator(Board& b, int player):
  board(b),
  player(player) {
  numMoves = 0;
}

void MoveGenerator::run() {
  runForPlayer();
  if (!numMoves) {
    player = 1 - player;
    runForPlayer();
  }
}

void MoveGenerator::runForPlayer() {
  int hand = board.inHand[player];
  while (hand) {
    int piece = __builtin_ctz(hand);
    runForPlayerPiece(piece);
    hand &= hand - 1;
  }
}

void MoveGenerator::runForPlayerPiece(int piece) {
  CornerList& cl = board.corners[player];
  for (int i = 0; i < cl.size; i++) {
    runForPlayerPieceCorner(piece, cl.list[i]);
  }
}

void MoveGenerator::runForPlayerPieceCorner(int piece, Cell c) {
  PieceSet* ps = board.pieceSet;
  int n = ps->numPlacements[piece][c.rank][c.file];
  for (int i = 0; i < n; i++) {
    int varId = ps->placements[piece][c.rank][c.file][i];
    tryPlacement(piece, varId);
  }
}

void MoveGenerator::tryPlacement(u8 piece, int varId) {
  Piece& var = board.pieceSet->variants[varId];
  if (board.accommodates(var, player)) {
    moves[numMoves++] = { varId, piece };
  }
}
