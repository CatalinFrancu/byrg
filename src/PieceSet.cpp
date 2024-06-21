#include "Bitmap.h"
#include "PieceSet.h"
#include <string.h>

void PieceSet::precompute() {
  memset(numShifts, 0, sizeof(numShifts));

  Bitmap bitmap;
  for (int i = 0; i < NUM_PIECES; i++) {
    pieces[i].numVariants = 0;
    bitmap.copyFrom(BITMAPS[i]);
    for (int mir = 0; mir < 2; mir++) {
      for (int rot = 0; rot < 4; rot++) {
        pieces[i].considerBitmap(bitmap);
        bitmap.rotate();
      }
      bitmap.mirror();
    }

    for (int j = 0; j < pieces[i].numVariants; j++) {
      tryAllShifts(i, j);
    }
  }
}

void PieceSet::tryAllShifts(int piece, int varId) {
  PieceVariant& var = pieces[piece].variants[varId];
  int width = var.width;
  int height = var.height;

  for (int dr = 0; dr <= BOARD_SIZE - height; dr++) {
    for (int dc = 0; dc <= BOARD_SIZE - width; dc++) {
      int shift = dr * BOARD_SIZE + dc;
      for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
          int src = r * BOARD_SIZE + c;
          if (var.mask.get(src)) {
            int dest = src + shift;
            u8& n = numShifts[piece][dest];
            shiftedMasks[piece][dest][n++] = var.mask << shift;
          }
        }
      }
    }
  }
}
