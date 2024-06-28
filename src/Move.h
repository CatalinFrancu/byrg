#pragma once

#include "globals.h"

class Move {

public:
  // Variant ID from the PieceSet.
  int varId;

  // Store which piece it was, so that we can remove it from the player's hand.
  u8 pieceId;

  bool isPass();
  void setPass();

private:
  static const int PASS = -1;

};
