#include "Bitset.h"
#include "globals.h"
#include <string>
#include <string.h>
#include "StrUtil.h"

void StrUtil::reverse(char* s) {
  int i = 0, j = strlen(s) - 1;
  while (i < j) {
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
    i++;
    j--;
  }
}

// TODO: This is O(n), should be O(number of bits set)
std::string StrUtil::moveToString(Bitset& mask) {
  std::string result = "";
  for (int rank = 0; rank < BOARD_SIZE; rank++) {
    for (int file = 0; file < BOARD_SIZE; file++) {
      if (mask.get(rank * BOARD_SIZE + file)) {
        if (result > "") {
          result += ',';
        }
        result += (file + 'a');
        result += std::to_string(rank + 1);
      }
    }
  }
  return result;
}

Bitset StrUtil::stringToMove(std::string& move) {
  Bitset mask;
  mask.clear();

  int p = 0, len = move.length();
  while (p < len) {
    int file = move[p++] - 'a';
    int rank = 0;
    while (std::isdigit(move[p])) {
      rank = rank * 10 + (move[p++] - '0');
    }
    rank--; // 0-based
    mask.set(rank * BOARD_SIZE + file);
    if (p < len) {
      p++; // skip the comma
    }
  }
  return mask;
}
