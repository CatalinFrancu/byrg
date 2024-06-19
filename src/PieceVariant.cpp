#include "PieceVariant.h"
#include <string>

bool PieceVariant::operator==(PieceVariant other) {
  if (size != other.size) {
    return false;
  }
  for (int i = 0; i < size; i++) {
    if (cells[i] != other.cells[i]) {
      return false;
    }
  }
  return true;
}

int PieceVariant::getWidth() {
  int result = 0;
  for (int i = 0; i < size; i++) {
    int file = cells[i] % PADDED_BOARD_SIZE;
    result = std::max(result, file);
  }
  return result;
}

int PieceVariant::getHeight() {
  int result = 0;
  for (int i = 0; i < size; i++) {
    int rank = cells[i] / PADDED_BOARD_SIZE;
    result = std::max(result, rank);
  }
  return result;
}

void PieceVariant::translate(int dr, int dc) {
  for (int i = 0; i < size; i++) {
    int rank = cells[i] / PADDED_BOARD_SIZE;
    int file = cells[i] % PADDED_BOARD_SIZE;
    cells[i] = (rank + dr) * PADDED_BOARD_SIZE + (file + dc);
  }
}

void PieceVariant::fromBitmap(Bitmap b) {
  size = 0;
  for (int r = 0; b.pixels[r][0]; r++) {
    for (int c = 0; b.pixels[r][c]; c++) {
      if (b.pixels[r][c] == '*') {
        cells[size++] = (r + 1) * PADDED_BOARD_SIZE + (c + 1);
      }
    }
  }
}

void PieceVariant::fromString(std::string s) {
  size = 0;

  int p = 0, len = s.length();
  while (p < len) {
    int file = s[p++] - 'a' + 1;
    int rank = 0;
    while (std::isdigit(s[p])) {
      rank = rank * 10 + (s[p++] - '0');
    }
    cells[size++] = rank * PADDED_BOARD_SIZE + file;
    p++; // skip the comma
  }
}

std::string PieceVariant::toString() {
  std::string result = "";
  for (int i = 0; i < size; i++) {
    if (result > "") {
      result += ',';
    }
    int rank = cells[i] / PADDED_BOARD_SIZE;
    int file = cells[i] % PADDED_BOARD_SIZE;
    result += (file - 1 + 'a');
    result += std::to_string(rank);
  }
  return result;
}
