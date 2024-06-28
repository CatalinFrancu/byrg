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

  static constexpr char ANSI_COLOR_BG[2][7] = {
    "\e[105m", "\e[43m",
  };
  static constexpr char ANSI_COLOR_FG[2][7] = {
    "\e[95m", "\e[33m",
  };
  static constexpr char DEFAULT_COLOR[11] = "\e[49m\e[39m";

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
  int stm = 0; // side to move
  int passCount = 0;

  PieceSet* pieceSet;

  void init();
  void setPlayer(int player);
  int getScore(int player);
  bool isFinal();
  int eval();

  void makeMove(Move& move);
  void makeMove(Move& move, UndoInfo* undo);
  void undoMove(Move& move, UndoInfo* undo);
  bool accommodates(Piece var);
  void print();
  void printCell(int rank, int file);

private:
  void initMatrix();
  void initPlayers();

  void setArea(Piece& p, int val);
  void updateCornerLists(Piece& piece, UndoInfo* undo);
};
