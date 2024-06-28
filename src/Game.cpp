#include <assert.h>
#include "Game.h"
#include "MoveGenerator.h"
#include <string>
#include "StrUtil.h"
#include "UndoInfo.h"

Game::Game() {
  pieceSet.precompute();
  board.pieceSet = &pieceSet;
}

bool Game::setType(std::string desc) {
  return (desc == "Blokus Duo");
}

void Game::restart() {
  board.init();
}

std::string Game::findMove(int player) {
  clock.start();
  posCount = moveCount = 0;

  // Take the arbiter's word that @player is the side to move and there are
  // legal moves.
  board.setPlayer(player);
  Move move;
  int score;
  alphaBetaWrapper(4, move, score);
  board.makeMove(move);
  board.print();
  fprintf(stderr, "Score: %d     Positions: %llu     Moves: %llu\n",
          score, posCount, moveCount);

  std::string str;
  if (move.isPass()) {
    str = "pass";
  } else {
    Piece p = pieceSet.variants[move.varId];
    str = p.toString();
  }

  clock.stop();
  return str;
}

void Game::alphaBetaWrapper(int depth, Move& move, int& score) {
  move.setPass();
  score = -(INFINITY+1); // even losing positions beat this

  MoveGenerator gen(board);
  while (!gen.isFinished()) {
    moveCount++;
    Move mv = gen.getMove();
    UndoInfo undo[2];
    board.makeMove(mv, undo);
    int child = -alphaBeta(depth - 1, -INFINITY, -score);
    board.undoMove(mv, undo);
    if (child > score) {
      score = child;
      move = mv;
    }
  }
}

int Game::alphaBeta(int depth, int alpha, int beta) {
  if ((depth == 0) || board.isFinal()) {
    posCount++;
    return board.eval();
  }

  MoveGenerator gen(board);

  while (!gen.isFinished()) {
    moveCount++;
    Move mv = gen.getMove();
    UndoInfo undo[2];
    board.makeMove(mv, undo);
    int child = -alphaBeta(depth - 1, -beta, -alpha);
    board.undoMove(mv, undo);

    if (child >= beta) {
      return beta;
    } else if (child > alpha) {
      alpha = child;
    }
  }

  return alpha;
}

void Game::makeMove(int player, std::string move) {
  Piece p;
  p.fromString(move);

  Move m = pieceSet.find(p);
  board.setPlayer(player);
  board.makeMove(m);
  board.print();
}

void Game::end() {
  fprintf(stderr, "Final score: %d %d\n", board.getScore(0), board.getScore(1));
}
