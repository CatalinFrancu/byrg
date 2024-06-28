#pragma once

#include "Move.h"

class SearchResult {
public:
  Move move;

  // Even losing final positions must be preferable to this.
  int score = -(INFINITY + 1);
};
