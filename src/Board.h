#pragma once

#include "globals.h"
#include "Cell.h"
#include "Move.h"
#include "PieceSet.h"
#include "Score.h"

class Board {
public:
  static const u8 EMPTY = 2;
  static constexpr Cell STARTING_POSITIONS[2] = { { 10, 5 }, { 5, 10 } };
  static const int COEF_POP = 4;
  static const int COEF_STONES = 1;

  static constexpr char ANSI_COLORS[2][7] = {
    "\e[105m", "\e[43m",
  };
  static constexpr char DEFAULT_COLOR[7] = "\e[49m";

  // 0-1 = used by player 0-1; EMPTY = empty
  u8 a[PADDED_BOARD_SIZE][PADDED_BOARD_SIZE];

  PieceSet* pieceSet;

  // bit masks of pieces still in hand
  int inHand[2];

  void init();

  Score eval();

  void setArea(int val, Move& move);
  void makeMove(int player, Move& move);
  void undoMove(int player, Move& move);
  int collectStones(int player, Cell* dest);
  bool accommodates(PieceVariant var, int player);
  void print();
  void printCell(int rank, int file);

private:
  void initMatrix();
  void initPlayerMasks();
};
