#pragma once

#include "globals.h"

class Bitset {
public:
  // All Bitsets have the same size.
  static const int SIZE = BOARD_SIZE * BOARD_SIZE;
  static const int WHOLE = SIZE / 64;
  static const int PART = SIZE % 64;
  static const int NONE = -1;

  void set(int pos);
  bool get(int pos);
  int count();
  bool any();
  bool none();
  void clear();

  // Finds, clears and returns the least significant set bit, or -1 if the
  // bitset is empty.
  int consumeBit();

  bool operator==(Bitset other);
  Bitset operator&(Bitset other);
  Bitset operator|(Bitset other);
  void operator|=(Bitset other);
  void operator^=(Bitset other);
  Bitset operator~();
  Bitset operator>>(int dist);
  void operator>>=(int dist);
  Bitset operator<<(int dist);
  void operator<<=(int dist);
  void copyFrom(const Bitset* src);
  void print(int width);

private:
  u64 buf[WHOLE + 1];
};