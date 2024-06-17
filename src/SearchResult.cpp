#include "globals.h"
#include "Score.h"
#include "SearchResult.h"

SearchResult SearchResult::minusInfinity() {
  SearchResult res;
  for (int i = 0; i < MAX_PLAYERS; i++) {
    res.score.val[i] = -Score::INFINITY;
  }
  return res;
}
