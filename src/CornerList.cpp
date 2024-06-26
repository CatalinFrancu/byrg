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
  if (where[(int)c.rank][(int)c.file] == NONE) {
    where[(int)c.rank][(int)c.file] = size;
    list[size++] = c;
    undo.added[undo.numAdded++] = c;
  }
}

void CornerList::fastAdd(Cell c) {
  where[(int)c.rank][(int)c.file] = size;
  list[size++] = c;
}

void CornerList::remove(Cell c, UndoInfo& undo) {
  int pos = where[(int)c.rank][(int)c.file];
  if (pos != NONE) {
    // superfluous if pos == size - 1, but saves a test
    Cell last = list[size - 1];
    where[(int)last.rank][(int)last.file] = pos;
    list[pos] = last;

    where[(int)c.rank][(int)c.file] = NONE;
    size--;

    undo.removed[undo.numRemoved++] = c;
  }
}

void CornerList::fastRemove(Cell c) {
  int pos = where[(int)c.rank][(int)c.file];
  Cell last = list[size - 1];
  where[(int)last.rank][(int)last.file] = pos;
  list[pos] = last;

  where[(int)c.rank][(int)c.file] = NONE;
  size--;
}

void CornerList::restore(UndoInfo& undo) {
  for (int i = 0; i < undo.numAdded; i++) {
    fastRemove(undo.added[i]);
  }
  for (int i = 0; i < undo.numRemoved; i++) {
    fastAdd(undo.removed[i]);
  }
  undo.numAdded = undo.numRemoved = 0;
}
