#include "assert.h"
#include "Bitmap.h"
#include "Board.h"
#include "globals.h"
#include "PieceSet.h"
#include <stdio.h>

Bitset Board::firstRank;
Bitset Board::lastRank;
Bitset Board::firstFile;
Bitset Board::lastFile;

void Board::init() {
  initBorderMasks();
  initPlayerMasks();
}

void Board::initBorderMasks() {
  int size = BOARD_SIZE;
  for (int i = 0; i < size; i++) {
    firstRank.set(i);
    lastRank.set(size * (size - 1) + i);
    firstFile.set(size * i);
    lastFile.set(size * i + size - 1);
  }
}

void Board::initPlayerMasks() {
  occ[0].clear();
  occ[1].clear();
  inHand[0] = inHand[1] = (1 << NUM_PIECES) - 1;
}

int Board::eval(int player) {
  return sideEval(player) - sideEval(1 - player);
}

int Board::sideEval(int player) {
  Bitset unavailable;
  Bitset stones;
  makeLandscape(player, unavailable, stones);
  return occ[player].count() * COEF_POP
      + stones.count() * COEF_STONES;
}

void Board::makeLandscape(int player, Bitset& unavailable, Bitset& stones) {
  Bitset& me = occ[player];
  int size = BOARD_SIZE;

  // Squares occupied by any player are unavailable.
  unavailable = occ[0] | occ[1];

  // Squares adjacent to my pieces are unavailable.
  unavailable |= (me & ~firstRank) >> size;
  unavailable |= (me & ~lastRank) << size;
  unavailable |= (me & ~firstFile) >> 1;
  unavailable |= (me & ~lastFile) << 1;

  // The piece must touch a stepping stone.
  if (me.any()) {
    stones =
      ((me & ~firstRank & ~firstFile) >> (size + 1)) |
      ((me & ~firstRank & ~lastFile) >> (size - 1)) |
      ((me & ~lastRank & ~firstFile) << (size - 1)) |
      ((me & ~lastRank & ~lastFile) << (size + 1));
  } else {
    stones = getStartingPos(player);
  }
}

Bitset Board::getStartingPos(int player) {
  Bitset result;
  result.clear();
  int pos = STARTING_POSITIONS[player];
  result.set(pos);
  return result;
}

void Board::makeMove(int player, Move& move) {
  occ[player] ^= move.mask;
  inHand[player] ^= (1 << move.piece);
}

void Board::undoMove(int player, Move& move) {
  // Identical, under the current board representation.
  makeMove(player, move);
}

int Board::getPieceFromMask(Bitset mask) {
  // Shift the mask towards the LSB
  while ((mask & firstRank).none()) {
    mask >>= BOARD_SIZE;
  }
  while ((mask & firstFile).none()) {
    mask >>= 1;
  }

  for (int p = 0; p < NUM_PIECES; p++) {
    Piece& piece = pieceSet->pieces[p];
    for (int rot = 0; rot < piece.numVariants; rot++) {
      if (piece.variants[rot].mask == mask) {
        return p;
      }
    }
  }
  assert(false);
}

void Board::print() {
  int size = BOARD_SIZE;
  for (int rank = size - 1; rank >= 0; rank--) {
    fprintf(stderr, "%2d ", rank + 1);
    for (int file = 0; file < size; file++) {
      int bit = rank * size + file;
      printBit(bit);
    }
    fprintf(stderr, "\n");
  }

  fprintf(stderr, "   ");
  for (int file = 0; file < size; file++) {
    fprintf(stderr, " %c", file + 'a');
  }
  fprintf(stderr, "\n");
}

void Board::printBit(int bit) {
  int p = 0;
  while ((p < 2) && !occ[p].get(bit)) {
    p++;
  }

  if (p == 2) {
    fprintf(stderr, "  ");
  } else {
    fprintf(stderr, "%s  %s", ANSI_COLORS[p], DEFAULT_COLOR);
  }
}
