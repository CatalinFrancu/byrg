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
  int numMoves;

  Bitset unavailable; // to the current player

  MoveGenerator(Board& board, int player);

  // Generates moves for the first player, beginning with @player, that still
  // has legal moves. Sets size = 0 if the game is over.
  void run();

private:
  void runForPlayer();
  void runForPlayerStone(int stone);
  void runForPlayerStoneVariant(int stone, int piece, int var);
  void runForPlayerStoneVariantShift(int piece, int var, int shift);
  void add(Bitset& mask, int piece);

};
