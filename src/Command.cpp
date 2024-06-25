#include "assert.h"
#include "Command.h"
#include <iostream>
#include "StrUtil.h"

void Command::readFromStdin() {
  std::string s;
  std::getline(std::cin, s);
  s = StrUtil::trim(s);
  std::string cmd = getToken(s);

  if (cmd == "set_game") {
    type = T_SET_GAME;
    strArg = s;
  } else if (cmd == "clear_board") {
    type = T_CLEAR_BOARD;
    strArg = "";
  } else if (cmd == "cputime") {
    type = T_CPUTIME;
    strArg = "";
  } else if (cmd == "genmove") {
    type = T_GENMOVE;
    intArg = getPlayerFromCode(s[0]); // we use 0-based player IDs
  } else if (cmd == "play") {
    type = T_PLAY;
    intArg = getPlayerFromCode(getToken(s)[0]);
    strArg = s;
  } else if (cmd == "quit") {
    type = T_QUIT;
    strArg = "";
  } else {
    type = T_UNKNOWN;
    strArg = cmd;
  }
}

std::string Command::getToken(std::string& s) {
  int pos = 0, len = s.length();
  while ((pos < len) && !std::isspace(s[pos])) {
    pos++;
  }

  std::string first = s.substr(0, pos);
  s = StrUtil::trim(s.substr(pos));
  return first;
}

int Command::getPlayerFromCode(char code) {
  switch (code) {
    case '1': return 0;
    case '2': return 1;
    case '3': return 2;
    case '4': return 3;
    case 'b': return 0;
    case 'w': return 1;
    default: assert(0);
  }
}
