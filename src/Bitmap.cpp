#include "Bitmap.h"
#include "Cell.h"
#include <string.h>
#include "StrUtil.h"

void Bitmap::copyFrom(Bitmap src) {
  int rows = src.getNumRows();

  for (int r = 0; r < rows; r++) {
    strcpy(pixels[r], src.pixels[r]);
  }
  pixels[rows][0] = '\0';
}

void Bitmap::rotate() {
  int rows = getNumRows(), cols = getNumCols();

  Bitmap tmp;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      tmp.pixels[cols - 1 - c][r] = pixels[r][c];
    }
  }
  for (int c = 0; c < cols; c++) {
    tmp.pixels[c][rows] = '\0';
  }
  tmp.pixels[cols][0] = '\0';

  copyFrom(tmp);
}

void Bitmap::mirror() {
  int rows = getNumRows();
  for (int r = 0; r < rows; r++) {
    StrUtil::reverse(pixels[r]);
  }
}

int Bitmap::getNumRows() {
  int rows = 0;
  while (pixels[rows][0]) {
    rows++;
  }

  return rows;
}

int Bitmap::getNumCols() {
  return strlen(pixels[0]);
}

bool Bitmap::occupied(int row, int col) {
  return (row >= 0) &&
    (row < getNumRows()) &&
    (col >= 0) &&
    (col <= getNumCols()) &&
    (pixels[row][col] == '*');
}

int Bitmap::getCorners(Cell* dest) {
  int rows = getNumRows();
  int cols = getNumCols();
  int n = 0;

  for (int r = -1; r <= rows; r++) {
    for (int c = -1; c <= cols; c++) {
      if (!occupied(r, c) &&
          !occupied(r - 1, c) &&
          !occupied(r, c - 1) &&
          !occupied(r + 1, c) &&
          !occupied(r, c + 1) &&
          (occupied(r - 1, c - 1) ||
           occupied(r - 1, c + 1) ||
           occupied(r + 1, c - 1) ||
           occupied(r + 1, c + 1))) {
        // 1-based
        dest[n++] = { (char)(r + 1), (char)(c + 1) };
      }
    }
  }

  return n;
}

int Bitmap::getNeighbors(Cell* dest) {
  int rows = getNumRows();
  int cols = getNumCols();
  int n = 0;

  for (int r = -1; r <= rows; r++) {
    for (int c = -1; c <= cols; c++) {
      if (!occupied(r, c) &&
          (occupied(r - 1, c) ||
           occupied(r, c - 1) ||
           occupied(r + 1, c) ||
           occupied(r, c + 1))) {
        // 1-based
        dest[n++] = { (char)(r + 1), (char)(c + 1) };
      }
    }
  }

  return n;
}
