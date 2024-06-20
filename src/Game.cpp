#include <assert.h>
#include "Game.h"
#include "MoveGenerator.h"
#include "Piece.h"
#include "SearchResult.h"
#include <string>
#include "StrUtil.h"

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
  SearchResult sr = minimax(player, 2);
  board.print();
  fprintf(stderr, "SCORE: %d\n", sr.score);
  board.makeMove(player, sr.move);
  std::string str = StrUtil::moveToString(sr.move.mask);
  clock.stop();

  return str;
}

SearchResult Game::minimax(int player, int depth) {
  SearchResult best;
  if (depth == 0) {
    best.score = board.eval(player);
    return best;
  }

  MoveGenerator gen(board, player);
  gen.run();

  if (!gen.numMoves) {
    best.score = board.eval(player);
    return best;
  }
  player = gen.player; // not necessarily the same

  best = SearchResult::minusInfinity();

  for (int i = 0; i < gen.numMoves; i++) {
    Move& mv = gen.moves[i];
    board.makeMove(player, mv);
    SearchResult sr = minimax(1 - player, depth - 1);
    if (-sr.score > best.score) {
      best = { mv, -sr.score };
    }
    board.undoMove(player, mv);
  }

  return best;
}

void Game::makeMove(int player, std::string move) {
  Move m;
  m.mask = StrUtil::stringToMove(move);
  m.piece = board.getPieceFromMask(m.mask);
  board.makeMove(player, m);
}
