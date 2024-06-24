#pragma once

#include "Bitmap.h"
#include "Cell.h"
#include <string>

class Piece {
public:
  Cell cells[MAX_PIECE_SIZE];
  u8 size;

  bool operator==(Piece other);

  int getWidth();
  int getHeight();
  void translate(int dr, int dc);

  void fromBitmap(Bitmap b);

  // Parses a Pentobi GTP move string. Populates cells[], but not corners[].
  void fromString(std::string s);
  std::string toString();
};
