#pragma once

#include "Args.h"
#include "Board.h"
#include "Clock.h"
#include <string>
#include <vector>

class Game {
public:
  Args args;
  PieceSet pieceSet;
  Board board;
  Clock clock;
  u64 posCount, moveCount;

  Game(Args& args);

  bool setType(std::string desc);
  void restart();

  // Find, make and return a move for player. The player is assumed to still
  // be in the game.
  std::string findMove(int player);
  void makeMove(int player, std::string move);
  void end();

private:
  static const int OPENING_MOVES = 2;
  static const int DEPTH_OPENING = 3;
  static const int DEPTH_REST = 4;

  int getDepth();
  std::vector<Move> randomizeMoves();
  void alphaBetaWrapper(int depth, Move& move, int& score);
  int alphaBeta(int depth, int alpha, int beta);

};
