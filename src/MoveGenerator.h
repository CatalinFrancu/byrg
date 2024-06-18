#pragma once

#include "globals.h"
#include "Bitset.h"
#include "Board.h"
#include "Move.h"

class MoveGenerator {
public:
  // TBD what is reasonable
  static const int MAX_MOVES = 1'000;

  Board& board;
  Move moves[MAX_MOVES];
  int player;
  int size;

  Bitset unavailable; // to the current player

  MoveGenerator(Board& board);

  // Generates moves for the first player, beginning with @player, that still
  // has legal moves. Sets size = 0 if the game is over.
  void run(int player);

private:
  void genMovesWithPiece(int player, int piece, int rot, Bitset& stones);
  void tryMove(int piece, Bitset& mask, Bitset& stones);
  void add(Bitset& mask, int piece);

};
