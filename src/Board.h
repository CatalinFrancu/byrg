#pragma once

#include "Cell.h"
#include "CornerList.h"
#include "globals.h"
#include "Move.h"
#include "PieceSet.h"
#include "UndoInfo.h"

class Board {
public:
  static const u8 EMPTY = 2;
  static constexpr Cell STARTING_POSITIONS[2] = { { 10, 5 }, { 5, 10 } };

  static constexpr char ANSI_COLORS[2][7] = {
    "\e[105m", "\e[43m",
  };
  static constexpr char DEFAULT_COLOR[7] = "\e[49m";

  static const int SCORE_OWN_PIECES = 10;
  static const int SCORE_OPP_PIECES = 10;
  static const int SCORE_OWN_CORNERS = 10;
  static const int SCORE_OPP_CORNERS = 2;
  static const int NO_HAND_BONUS = 15;

  // 0-1 = used by player 0-1; EMPTY = empty
  u8 a[PADDED_BOARD_SIZE][PADDED_BOARD_SIZE];
  int count[3]; // include count for EMPTY
  CornerList corners[2];

  // bit masks of pieces still in hand
  int inHand[2];

  PieceSet* pieceSet;

  void init();
  int getScore(int player);

  int eval(int player);

  void makeMove(int player, Move& move);
  void makeMove(int player, Move& move, UndoInfo* undo);
  void undoMove(int player, Move& move, UndoInfo* undo);
  bool accommodates(Piece var, int player);
  void print();
  void printCell(int rank, int file);

private:
  void initMatrix();
  void initPlayerMasks();
  void initCornerLists();

  void setArea(Piece& p, int val);
  void updateCornerLists(int player, Piece& piece, UndoInfo* undo);
  void undoCornerLists(int player, UndoInfo* undo);

  bool isAvailable(int player, int rank, int file);
};
