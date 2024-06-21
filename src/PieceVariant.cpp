#include "PieceVariant.h"
#include <string.h>

void PieceVariant::fromBitmap(Bitmap b) {
  mask.clear();
  height = 0;
  width = strlen(b.pixels[0]);

  for (int r = 0; b.pixels[r][0]; r++) {
    height++;
    for (int c = 0; b.pixels[r][c]; c++) {
      if (b.pixels[r][c] == '*') {
        int bit = r * BOARD_SIZE + c;
        mask.set(bit);
      }
    }
  }
}
