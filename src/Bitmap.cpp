#include "Bitmap.h"
#include <string.h>
#include "StrUtil.h"

void Bitmap::copyFrom(Bitmap src) {
  int r = 0;
  while (src.pixels[r][0]) {
    strcpy(pixels[r], src.pixels[r]);
    r++;
  }
  pixels[r][0] = '\0';
}

void Bitmap::rotate() {
  int rows = 0, cols = strlen(pixels[0]);
  while (pixels[rows][0]) {
    rows++;
  }

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
  for (int r = 0; pixels[r][0]; r++) {
    StrUtil::reverse(pixels[r]);
  }
}

int Bitmap::getSize() {
  int result = 0;
  for (int r = 0; pixels[r][0]; r++) {
    for (int c = 0; pixels[r][c]; c++) {
      result += (pixels[r][c] == '*');
    }
  }
  return result;
}
