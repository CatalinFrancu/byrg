#include "Cell.h"
#include <string>

bool Cell::operator==(Cell other) {
  return (rank == other.rank) && (file == other.file);
}

bool Cell::onBoard() {
  return (rank > 0) && (rank <= BOARD_SIZE) &&
    (file > 0) && (file <= BOARD_SIZE);
}

void Cell::set(int rank, int file) {
  this->rank = rank;
  this->file = file;
}

void Cell::translate(int dr, int df) {
  rank += dr;
  file += df;
}

std::string Cell::toString() {
  return (char)(file - 1 + 'a') + std::to_string(rank);
}
