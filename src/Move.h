#pragma once

#include "globals.h"

class Move {

public:
  // Store the piece mask, but also which piece it was, so that we can remove
  // it from the player's hand.
  bitset mask;
  unsigned char piece;
};
