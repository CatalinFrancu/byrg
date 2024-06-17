#pragma once

#include "globals.h"
#include "Move.h"

class MoveList {
public:
  // TBD what is reasonable
  static const int MAX_MOVES = 1'000;

  Move moves[MAX_MOVES];

  int player;
  int size;

  void add(bitset& mask, int piece);
};
