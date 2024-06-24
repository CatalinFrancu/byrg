#pragma once

#include "globals.h"
#include <string>

class PackedCell {
public:
  u8 val;

  bool operator==(PackedCell other);
  void set(int rank, int file);

  int getRank();
  int getFile();

  std::string toString();
};
