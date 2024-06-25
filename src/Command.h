#pragma once

#include <string>

class Command {
public:
  static const int T_UNKNOWN = 0;
  static const int T_SET_GAME = 1;
  static const int T_CLEAR_BOARD = 2;
  static const int T_CPUTIME = 3;
  static const int T_GENMOVE = 4;
  static const int T_PLAY = 5;
  static const int T_QUIT = 6;

  int type = T_UNKNOWN;
  std::string strArg;
  int intArg;

  void readFromStdin();

private:
  std::string getToken(std::string& s);
  int getPlayerFromCode(char code);
};
