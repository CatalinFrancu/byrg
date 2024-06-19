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
  Bitset stones;
  board.makeLandscape(player, unavailable, stones);

  int stone;
  while ((stone = stones.consumeBit()) != Bitset::NONE) {
    runForPlayerStone(stone);
  }
}

void MoveGenerator::runForPlayerStone(int stone) {
  int hand = board.inHand[player];
  while (hand) {
    int piece = __builtin_ctz(hand);
    for (int var = 0; var < board.pieceSet->pieces[piece].numVariants; var++) {
      runForPlayerStoneVariant(stone, piece, var);
    }
    hand &= hand - 1;
  }
}

void MoveGenerator::runForPlayerStoneVariant(int stone, int piece, int var) {
  Piece& p = board.pieceSet->pieces[piece];
  PieceVariant& v = p.variants[var];
  int srow = stone / BOARD_SIZE;
  int scol = stone % BOARD_SIZE;

  for (int i = 0; i < p.size; i++) {
    int cell = v.bits[i];
    // Check whether we can translate @var to overlap @cell and @stone.
    int crow = cell / BOARD_SIZE;
    int ccol = cell % BOARD_SIZE;

    if ((srow >= crow) &&
        (srow <= BOARD_SIZE - v.height + crow) &&
        (scol >= ccol) &&
        (scol <= BOARD_SIZE - v.width + ccol)) {
      runForPlayerStoneVariantShift(piece, var, stone - cell);
    }
  }
}

void MoveGenerator::runForPlayerStoneVariantShift(int piece, int var, int shift) {
  Piece& p = board.pieceSet->pieces[piece];
  PieceVariant& v = p.variants[var];

  Bitset b = v.mask << shift;

  if ((b & unavailable).none()) {
    add(b, piece);
  }
}

void MoveGenerator::add(Bitset& mask, int piece) {
  moves[numMoves].mask = mask;
  moves[numMoves].piece = piece;
  numMoves++;
}
