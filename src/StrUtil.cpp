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

std::string StrUtil::trim(std::string s) {
  int l = 0, r = s.length();

  while ((l < r) && std::isspace(s[l])) {
    l++;
  }
  while ((r > l) && std::isspace(s[r - 1])) {
    r--;
  }
  return s.substr(l, r - l);
}
