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
  numStones = board.collectStones(player, stones);

  int hand = board.inHand[player];
  while (hand) {
    int piece = __builtin_ctz(hand);
    runForPlayerPiece(piece);
    hand &= hand - 1;
  }
}

void MoveGenerator::runForPlayerPiece(int piece) {
  for (int i = 0; i < numStones; i++) {
    runForPlayerPieceStone(piece, stones[i]);
  }
}

void MoveGenerator::runForPlayerPieceStone(int piece, Cell stone) {
  PieceSet* ps = board.pieceSet;
  int n = ps->numPlacements[piece][stone.r][stone.c];
  for (int i = 0; i < n; i++) {
    int placement = ps->placements[piece][stone.r][stone.c][i];
    tryPlacement(piece, placement);
  }
}

void MoveGenerator::tryPlacement(u8 piece, int varId) {
  PieceVariant& var = board.pieceSet->variants[varId];
  if (board.accommodates(var, player)) {
    moves[numMoves++] = { varId, piece };
  }
}
