#pragma once

#include "globals.h"

class Bitset {
public:
  // All Bitsets have the same size.
  static int size, whole, part;

  static void setSize(int size);

  void set(int pos);
  bool get(int pos);
  int count();
  bool any();
  bool none();
  void clear();
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
  u64 buf[MAX_CELLS / 64 + 1];
};
