#include "Bitmap.h"
#include "PieceSet.h"

void PieceSet::precompute() {
  Bitmap bitmap;
  for (int i = 0; i < NUM_PIECES; i++) {
    pieces[i].numVariants = 0;
    bitmap.copyFrom(BITMAPS[i]);
    for (int mir = 0; mir < 2; mir++) {
      for (int rot = 0; rot < 4; rot++) {
        pieces[i].considerBitmap(bitmap, BOARD_SIZE);
        bitmap.rotate();
      }
      bitmap.mirror();
    }
  }
}
