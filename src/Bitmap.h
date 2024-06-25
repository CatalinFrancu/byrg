#pragma once

#include "Cell.h"
#include "globals.h"

class Bitmap {
public:
  char pixels[MAX_PIECE_SIZE + 1][MAX_PIECE_SIZE + 1];

  void copyFrom(Bitmap src);
  void rotate();
  void mirror();

  int getNeighbors(Cell* dest);
  int getCorners(Cell* dest);

private:
  bool occupied(int row, int col);
  int getNumRows();
  int getNumCols();
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
