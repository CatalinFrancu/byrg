#include "Bitmap.h"
#include "Move.h"
#include "PieceSet.h"
#include <string.h>

void PieceSet::precompute() {
  memset(numPlacements, 0, sizeof(numPlacements));
  numVariants = 0;
  Bitmap bitmap;

  for (int i = 0; i < NUM_PIECES; i++) {
    numDistinct = 0;
    bitmap.copyFrom(BITMAPS[i]);
    for (int mir = 0; mir < 2; mir++) {
      for (int rot = 0; rot < 4; rot++) {
        Piece p;
        p.fromBitmap(bitmap);
        if (isDistinct(p)) {
          tryAllShifts(i, p);
        }
        bitmap.rotate();
      }
      bitmap.mirror();
    }
  }
}

bool PieceSet::isDistinct(Piece p) {
  distinct[numDistinct] = p;

  // Check if the new variant is distinct from all the others.
  int i = 0;
  while (distinct[i] != p) {
    i++;
  }
  if (i == numDistinct) {
    numDistinct++;
    return true;
  } else {
    return false;
  }
}

void PieceSet::tryAllShifts(int piece, Piece var) {
  int width = var.getWidth();
  int height = var.getHeight();

  for (int dr = 0; dr <= BOARD_SIZE - height; dr++) {
    for (int dc = 0; dc <= BOARD_SIZE - width; dc++) {
      Piece v = var;
      v.translate(dr, dc);
      addPlacements(piece, v);
    }
  }
}

void PieceSet::addPlacements(int piece, Piece var) {
  for (int i = 0; i < var.size; i++) {
    int rank = var.cells[i].rank;
    int file = var.cells[i].file;
    int &n = numPlacements[piece][rank][file];
    placements[piece][rank][file][n++] = numVariants;
  }
  variants[numVariants++] = var;
}

Move PieceSet::find(Piece var) {
  int rank = var.cells[0].rank;
  int file = var.cells[0].file;

  for (u8 piece = 0; piece < NUM_PIECES; piece++) {
    for (int i = 0; i < numPlacements[piece][rank][file]; i++) {
      int varId = placements[piece][rank][file][i];
      Piece& cand = variants[varId];
      if (cand == var) {
        return { varId, piece };
      }
    }
  }

  return { 0, 0 };
}
