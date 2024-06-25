#pragma once

class UndoInfo {
public:
  Cell added[MAX_CORNERS];
  Cell removed[MAX_PIECE_SIZE + MAX_NEIGHBORS];
  int numAdded = 0, numRemoved = 0;
};
