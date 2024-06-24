#pragma once

#include "Cell.h"
#include "globals.h"

class Bitmap {
public:
  char pixels[MAX_PIECE_SIZE + 1][MAX_PIECE_SIZE + 1];

  void copyFrom(Bitmap src);
  void rotate();
  void mirror();

  int getNumRows();
  int getNumCols();
  bool occupied(int row, int col);
  int getCorners(Cell* dest);
};

const Bitmap BITMAPS[NUM_PIECES] = {
  {
    "*..",
    "*..",
    "***",
  }, {
    "*.",
    "*.",
    "*.",
    "**",
  }, {
    "**.",
    ".*.",
    ".**",
  }, {
    ".*",
    ".*",
    "**",
    "*.",
  }, {
    "*..",
    "**.",
    ".**",
  }, {
    ".*.",
    "***",
    ".*.",
  }, {
    ".**",
    "**.",
    ".*.",
  }, {
    "*",
    "*",
    "*",
    "*",
    "*",
  }, {
    "***",
    ".*.",
    ".*.",
  }, {
    ".*",
    "**",
    ".*",
    ".*",
  }, {
    "**",
    "**",
    "*.",
  }, {
    "*.*",
    "***",
  }, {
    "*.",
    "*.",
    "**",
  }, {
    "*",
    "*",
    "*",
    "*",
  }, {
    "***",
    ".*.",
  }, {
    "**.",
    ".**",
  }, {
    "**",
    "**",
  }, {
    "*.",
    "**",
  }, {
    "*",
    "*",
    "*",
  }, {
    "**",
  }, {
    "*",
  },
};
