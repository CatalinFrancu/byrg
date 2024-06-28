#pragma once

#include "Cell.h"
#include "globals.h"
#include "UndoInfo.h"

class CornerList {
public:
  static const int NONE = -1;

  char where[PADDED_BOARD_SIZE][PADDED_BOARD_SIZE];
  Cell list[MAX_CORNERS];
  int size;

  void init(Cell startPos);
  bool contains(Cell c);
  void add(Cell c, UndoInfo& undo);
  void remove(Cell c, UndoInfo& undo);
  void restore(UndoInfo& undo);
  int copy(Cell* dest);

private:
  void fastAdd(Cell c);
  void fastRemove(Cell c);
};
