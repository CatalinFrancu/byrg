#pragma once

#include "globals.h"
#include "Board.h"
#include "Move.h"

class MoveGenerator {
public:
  // TBD what is reasonable
  static const int MAX_MOVES = 3'000;

  Board& board;
  Move moves[MAX_MOVES];
  int numMoves;

  MoveGenerator(Board& board);

  // Generates moves for the first player, beginning with @player, that still
  // has legal moves. Sets numMoves = 0 if the game is over.
  void run();

private:
  void tryEveryPiece();
  void tryEveryCorner(int piece);
  void tryEveryShape(int piece, Cell corner);
  void tryShape(u8 piece, int varId);
  void passIfNoMoves();
};
