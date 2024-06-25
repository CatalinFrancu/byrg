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
  int numStones;
  Cell* stones;
  int player;
  int numMoves;

  MoveGenerator(Board& board, int player);

  // Generates moves for the first player, beginning with @player, that still
  // has legal moves. Sets size = 0 if the game is over.
  void run();

private:
  void runForPlayer();
  void runForPlayerPiece(int piece);
  void runForPlayerPieceStone(int piece, Cell stone);
  void tryPlacement(u8 piece, int varId);
};
