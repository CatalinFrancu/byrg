#pragma once

#include "Move.h"

class SearchResult {
public:
  static const int INFINITY = 2'000'000'000;
  Move move;
  int score;

  static SearchResult minusInfinity();
};
