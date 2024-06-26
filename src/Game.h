#pragma once

#include "Board.h"
#include "Clock.h"
#include <string>

class Game {
public:
  PieceSet pieceSet;
  Board board;
  Clock clock;
  u64 posCount, moveCount;

  Game();

  bool setType(std::string desc);
  void restart();

  // Find, make and return a move for player. The player is assumed to still
  // be in the game.
  std::string findMove(int player);
  void makeMove(int player, std::string move);
  void end();

private:
  void alphaBetaWrapper(int depth, Move& move, int& score);
  int alphaBeta(int depth, int alpha, int beta);

};
