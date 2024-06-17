#include "MoveList.h"

void MoveList::add(bitset& mask, int piece) {
  moves[size].mask = mask;
  moves[size].piece = piece;
  size++;
}
