#pragma once

#include "Bitmap.h"
#include <string>

class PieceVariant {
public:
  u8 cells[MAX_PIECE_SIZE];
  u8 size;

  bool operator==(PieceVariant other);

  int getWidth();
  int getHeight();
  void translate(int dr, int dc);

  void fromBitmap(Bitmap b);
  void fromString(std::string s);
  std::string toString();
};
