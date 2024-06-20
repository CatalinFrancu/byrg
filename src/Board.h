#pragma once

#include "globals.h"
#include "Bitset.h"
#include "Move.h"
#include "PieceSet.h"

class Board {
public:
  static constexpr int STARTING_POSITIONS[2] = { 130, 65 };
  static const int COEF_POP = 4;
  static const int COEF_STONES = 1;

  static constexpr char ANSI_COLORS[2][7] = {
    "\e[105m", "\e[43m",
  };
  static constexpr char DEFAULT_COLOR[7] = "\e[49m";

  // border masks to be used during the move generation
  static Bitset firstRank, lastRank, firstFile, lastFile;
  PieceSet* pieceSet;

  // occupancy per player
  Bitset occ[2];

  // bit masks of pieces still in hand
  int inHand[2];

  void init();

  void makeLandscape(int player, Bitset& unavailable, Bitset& stones);
  Bitset getStartingPos(int player);
  int eval(int player);
  int sideEval(int player);

  void makeMove(int player, Move& move);
  void undoMove(int player, Move& move);
  int getPieceFromMask(Bitset mask);
  void print();
  void printBit(int bit);

private:
  void initBorderMasks();
  void initPlayerMasks();
};
