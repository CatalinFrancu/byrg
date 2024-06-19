#pragma once

#include "Bitset.h"
#include <string>

class StrUtil {
public:
  static void reverse(char* s);
  static std::string moveToString(Bitset& mask);
  static Bitset stringToMove(std::string& move);
};
