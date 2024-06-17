#pragma once

#include "Move.h"
#include "Score.h"

class SearchResult {
public:
  Move move;
  Score score;

  static SearchResult minusInfinity();
};
