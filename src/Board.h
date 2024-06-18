#pragma once

#include "globals.h"
#include "Bitset.h"
#include "Move.h"
#include "Piece.h"
#include "Score.h"

class Board {
public:
  static const int T_DUO = 0;
  static const int T_CLASSIC = 1;
  static const int NUM_TYPES = 2;
  static const int SIZES[];
  static const int NUM_PLAYERS[];
  static const int STARTING_POSITIONS[][MAX_PLAYERS];
  static const int COEF_POP = 4;
  static const int COEF_STONES = 1;

  static constexpr char ANSI_COLORS[MAX_PLAYERS][7] = {
    "\e[106m", "\e[103m", "\e[101m", "\e[102m",
  };
  static constexpr char DEFAULT_COLOR[7] = "\e[49m";

  u8 type;   // 2-player Duo or 4-player Classic

  // border masks to be used during the move generation
  static Bitset firstRank, lastRank, firstFile, lastFile;

  Piece pieces[NUM_PIECES];

  // occupancy per player
  Bitset occ[MAX_PLAYERS];

  // bit masks of pieces still in hand
  int inHand[MAX_PLAYERS];

  int getSize();
  int getNumPlayers();
  void init(int type);

  void makeLandscape(int player, Bitset& unavailable, Bitset& stones);
  Bitset getStartingPos(int player);
  Score eval();

  void makeMove(int player, Move& move);
  void undoMove(int player, Move& move);
  int getPieceFromMask(Bitset mask);
  void print();
  void printBit(int bit);

private:
  void initBorderMasks();
  void initPlayerMasks();
  void initPieces();
};
