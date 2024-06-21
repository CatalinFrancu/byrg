#pragma once

class Move {

public:
  // Variant ID from the PieceSet.
  int varId;

  // Store which piece it was, so that we can remove it from the player's hand.
  u8 pieceId;
};
