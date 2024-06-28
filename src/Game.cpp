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

  // Take the arbiter's word that @player is the side to move and there are
  // legal moves.
  board.setPlayer(player);
  SearchResult sr = alphaBeta(4, -INFINITY, +INFINITY);
  board.makeMove(sr.move);
  board.print();
  fprintf(stderr, "Score: %d     Positions: %llu\n", sr.score, evalCount);
  Piece p = pieceSet.variants[sr.move.varId];
  std::string str = p.toString();
  clock.stop();

  return str;
}

SearchResult Game::alphaBeta(int depth, int alpha, int beta) {
  if ((depth == 0) || board.isFinal()) {
    return leafEval();
  }

  SearchResult best;
  MoveGenerator gen(board);
  gen.run();

  for (int i = 0; i < gen.numMoves; i++) {
    Move& mv = gen.moves[i];
    UndoInfo undo[2];
    board.makeMove(mv, undo);
    SearchResult sr = alphaBeta(depth - 1, -beta, -alpha);
    sr.score = -sr.score;
    board.undoMove(mv, undo);

    if (sr.score >= beta) {
      return { mv, beta };
    } else if (sr.score > alpha) {
      alpha = sr.score;
      best = { mv, sr.score };
    }
  }

  return best;
}

SearchResult Game::leafEval() {
  SearchResult s;
  s.score = board.eval();
  evalCount++;
  return s;
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
