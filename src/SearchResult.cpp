#include "globals.h"
#include "Score.h"
#include "SearchResult.h"

SearchResult SearchResult::minusInfinity() {
  SearchResult res;
  res.score.val[0] = res.score.val[1] = -Score::INFINITY;
  return res;
}
