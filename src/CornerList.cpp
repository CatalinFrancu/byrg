#include "CornerList.h"

void CornerList::init(Cell startPos) {
  for (int r = 0; r < PADDED_BOARD_SIZE; r++) {
    for (int c = 0; c < PADDED_BOARD_SIZE; c++) {
      where[r][c] = NONE;
    }
  }
  size = 0;
  UndoInfo ignored;
  add(startPos, ignored);
}

void CornerList::add(Cell c, UndoInfo& undo) {
  if (where[c.rank][c.file] == NONE) {
    where[c.rank][c.file] = size;
    list[size++] = c;
    undo.added[undo.numAdded++] = c;
  }
}

void CornerList::remove(Cell c, UndoInfo& undo) {
  int pos = where[c.rank][c.file];
  if (pos != NONE) {
    // superfluous if pos == size - 1, but saves a test
    Cell last = list[size - 1];
    where[last.rank][last.file] = pos;
    list[pos] = last;

    where[c.rank][c.file] = NONE;
    size--;

    undo.removed[undo.numRemoved++] = c;
  }
}

void CornerList::restore(UndoInfo& undo) {
  UndoInfo ignored;
  for (int i = 0; i < undo.numAdded; i++) {
    remove(undo.added[i], ignored);
  }
  for (int i = 0; i < undo.numRemoved; i++) {
    add(undo.removed[i], ignored);
  }
  undo.numAdded = undo.numRemoved = 0;
}
