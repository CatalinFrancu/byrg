#include <assert.h>
#include "Game.h"
#include "MoveGenerator.h"
#include "SearchResult.h"
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
  evalCount = 0;
  SearchResult sr = minimax(player, 2);
  board.makeMove(player, sr.move);
  board.print();
  fprintf(stderr, "Score: %d     Positions: %llu\n", sr.score, evalCount);
  Piece p = pieceSet.variants[sr.move.varId];
  std::string str = p.toString();
  clock.stop();

  return str;
}

SearchResult Game::minimax(int player, int depth) {
  if (depth == 0) {
    return leafEval(player);
  }

  MoveGenerator gen(board, player);
  gen.run();

  if (!gen.numMoves) {
    return leafEval(player);
  }
  player = gen.player; // not necessarily the same

  UndoInfo undo[2];
  SearchResult best;

  for (int i = 0; i < gen.numMoves; i++) {
    Move& mv = gen.moves[i];
    board.makeMove(player, mv, undo);
    SearchResult sr = minimax(1 - player, depth - 1);
    if (-sr.score > best.score) {
      best = { mv, -sr.score };
    }
    board.undoMove(player, mv, undo);
  }

  return best;
}

SearchResult Game::leafEval(int player) {
  SearchResult s;
  s.score = board.eval(player);
  evalCount++;
  return s;
}

void Game::makeMove(int player, std::string move) {
  Piece p;
  p.fromString(move);

  Move m = pieceSet.find(p);
  board.makeMove(player, m);
}

void Game::end() {
  fprintf(stderr, "Final score: %d %d\n", board.getScore(0), board.getScore(1));
}
