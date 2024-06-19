#include "globals.h"
#include "SearchResult.h"

SearchResult SearchResult::minusInfinity() {
  SearchResult res;
  res.score = -INFINITY;
  return res;
}
