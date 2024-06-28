#include "Move.h"

bool Move::isPass() {
  return varId == PASS;
}

void Move::setPass() {
  varId = PASS;
}
