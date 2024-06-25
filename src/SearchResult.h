#pragma once

#include "Move.h"

class SearchResult {
public:
  Move move;
  int score = -INFINITY;
};
