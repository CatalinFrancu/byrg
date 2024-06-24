#include "Piece.h"
#include <string>

bool Piece::operator==(Piece other) {
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

int Piece::getWidth() {
  int result = 0;
  for (int i = 0; i < size; i++) {
    int file = cells[i].file;
    result = std::max(result, file);
  }
  return result;
}

int Piece::getHeight() {
  int result = 0;
  for (int i = 0; i < size; i++) {
    int rank = cells[i].rank;
    result = std::max(result, rank);
  }
  return result;
}

void Piece::translate(int dr, int dc) {
  for (int i = 0; i < size; i++) {
    cells[i].translate(dr, dc);
  }
}

void Piece::fromBitmap(Bitmap b) {
  size = 0;
  for (int r = 0; b.pixels[r][0]; r++) {
    for (int c = 0; b.pixels[r][c]; c++) {
      if (b.pixels[r][c] == '*') {
        cells[size++].set(r + 1, c + 1);
      }
    }
  }
}

void Piece::fromString(std::string s) {
  size = 0;

  int p = 0, len = s.length();
  while (p < len) {
    int file = s[p++] - 'a' + 1;
    int rank = 0;
    while (std::isdigit(s[p])) {
      rank = rank * 10 + (s[p++] - '0');
    }
    cells[size++].set(rank, file);
    p++; // skip the comma
  }
}

std::string Piece::toString() {
  std::string result = "";
  for (int i = 0; i < size; i++) {
    if (result > "") {
      result += ',';
    }
    result += cells[i].toString();
  }
  return result;
}
