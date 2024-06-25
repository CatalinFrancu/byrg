#pragma once

#include "Cell.h"
#include "globals.h"
#include "UndoInfo.h"

class CornerList {
public:
  static const int NONE = -1;

  char where[PADDED_BOARD_SIZE][PADDED_BOARD_SIZE];
  Cell list[MAX_STONES];
  int size;

  void init(Cell startPos);
  void add(Cell c, UndoInfo& undo);
  void remove(Cell c, UndoInfo& undo);
  void restore(UndoInfo& undo);
};
