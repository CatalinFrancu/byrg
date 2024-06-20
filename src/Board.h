#pragma once

#include "globals.h"
#include "Cell.h"
#include "Move.h"
#include "PieceSet.h"

class Board {
public:
  static const u8 EMPTY = 2;
  static const u8 MAX_DIST = 255;
  static constexpr Cell STARTING_POSITIONS[2] = { { 10, 5 }, { 5, 10 } };

  static constexpr char ANSI_COLORS[2][7] = {
    "\e[105m", "\e[43m",
  };
  static constexpr char DEFAULT_COLOR[7] = "\e[49m";

  static const int SCORE_DEAD = 200;
  static const int SCORE_SELF = 1;
  static const int SCORE_OPP = 1;
  static const int SCORE_LARGE_PIECES = 2;

  // 0-1 = used by player 0-1; EMPTY = empty
  u8 a[PADDED_BOARD_SIZE][PADDED_BOARD_SIZE];

  PieceSet* pieceSet;

  // bit masks of pieces still in hand
  int inHand[2];

  // used during the eval BFS
  // TODO: These are only used for Minimax leaves
  u8 dist[PADDED_BOARD_SIZE][PADDED_BOARD_SIZE];
  Cell queue[PADDED_BOARD_SIZE * PADDED_BOARD_SIZE];
  int head, tail;

  void init();

  int eval(int player);
  int playerEval(int player);
  int sumStoneDist(int player);
  void bfsInit(int player);
  void bfs(int player);
  void bfsExtend(int player, u8 r, u8 c, int d);
  int bfsCollect(int player);

  void setArea(int val, Move& move);
  void makeMove(int player, Move& move);
  void undoMove(int player, Move& move);
  int collectStones(int player, Cell* dest);
  bool accommodates(PieceVariant var, int player);
  bool isAvailable(int player, int rank, int file);
  void print();
  void printCell(int rank, int file);

private:
  void initMatrix();
  void initPlayerMasks();
};
