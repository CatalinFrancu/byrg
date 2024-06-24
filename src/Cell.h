#pragma once

#include "globals.h"
#include <string>

struct Cell {
public:
  // Allow negative values for corners (before translations).
  char rank, file;


  bool operator==(Cell other);
  void set(int rank, int file);
  void translate(int dr, int df);
  std::string toString();
};
