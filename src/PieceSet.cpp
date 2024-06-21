#include "Bitmap.h"
#include "Move.h"
#include "PieceSet.h"
#include <string.h>

void PieceSet::precompute() {
  memset(numPlacements, 0, sizeof(numPlacements));
  numVariants = 0;
  Bitmap bitmap;

  for (int i = 0; i < NUM_PIECES; i++) {
    bitmap.copyFrom(BITMAPS[i]);
    for (int mir = 0; mir < 2; mir++) {
      for (int rot = 0; rot < 4; rot++) {
        PieceVariant var;
        var.fromBitmap(bitmap);
        if (pieces[i].addIfDistinct(var)) {
          tryAllShifts(i, var);
        }
        bitmap.rotate();
      }
      bitmap.mirror();
    }
  }
}

void PieceSet::tryAllShifts(int piece, PieceVariant var) {
  int width = var.getWidth();
  int height = var.getHeight();

  for (int dr = 0; dr <= BOARD_SIZE - height; dr++) {
    for (int dc = 0; dc <= BOARD_SIZE - width; dc++) {
      PieceVariant v = var;
      v.translate(dr, dc);
      addPlacements(piece, v);
    }
  }
}

void PieceSet::addPlacements(int piece, PieceVariant var) {
  for (int i = 0; i < var.size; i++) {
    int rank = var.cells[i] / PADDED_BOARD_SIZE;
    int file = var.cells[i] % PADDED_BOARD_SIZE;
    int &n = numPlacements[piece][rank][file];
    placements[piece][rank][file][n++] = numVariants;
  }
  variants[numVariants++] = var;
}

Move PieceSet::find(PieceVariant var) {
  Move m;
  int rank = var.cells[0] / PADDED_BOARD_SIZE;
  int file = var.cells[0] % PADDED_BOARD_SIZE;

  for (u8 piece = 0; piece < NUM_PIECES; piece++) {
    for (int i = 0; i < numPlacements[piece][rank][file]; i++) {
      int varId = placements[piece][rank][file][i];
      PieceVariant& cand = variants[varId];
      if (cand == var) {
        return { varId, piece };
      }
    }
  }

  return { 0, 0 };
}
