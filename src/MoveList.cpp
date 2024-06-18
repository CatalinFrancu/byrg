#include "MoveList.h"

void MoveList::add(Bitset& mask, int piece) {
  moves[size].mask = mask;
  moves[size].piece = piece;
  size++;
}
