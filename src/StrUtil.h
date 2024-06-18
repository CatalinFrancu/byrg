#pragma once

#include "Bitset.h"
#include <string>

class StrUtil {
public:
  static void reverse(char* s);
  static std::string moveToString(Bitset& mask, int size);
  static Bitset stringToMove(std::string& move, int size);
};
