#pragma once

#include "Bitmap.h"
#include "Cell.h"
#include <string>

class Piece {
public:
  Cell cells[MAX_PIECE_SIZE];
  Cell corners[MAX_CORNERS];
  u8 size, numCorners;

  bool operator==(Piece other);

  int getWidth();
  int getHeight();

  // Translates a bitmap (cells[] and corners[]). Only retains correct corners.
  void translate(int dr, int dc);

  // Parses a Bitmap. Populates cells[] and corners[]. Corners may have
  // negative coordinates.
  void fromBitmap(Bitmap b);

  // Parses a Pentobi GTP move string. Populates cells[], but not corners[].
  void fromString(std::string s);
  std::string toString();

private:
  void filterOnBoardCorners();
};
