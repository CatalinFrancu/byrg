#include "PackedCell.h"
#include <string>

bool PackedCell::operator==(PackedCell other) {
  return val == other.val;
}

void PackedCell::set(int rank, int file) {
  val = rank * PADDED_BOARD_SIZE + file;
}

int PackedCell::getRank() {
  return val / PADDED_BOARD_SIZE;
}

int PackedCell::getFile() {
  return val % PADDED_BOARD_SIZE;
}

std::string PackedCell::toString() {
  return (char)(getFile() - 1 + 'a') + std::to_string(getRank());
}
