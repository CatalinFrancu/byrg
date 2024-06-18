#include <assert.h>
#include "Game.h"
#include "MoveGenerator.h"
#include "Piece.h"
#include "SearchResult.h"
#include <string>
#include "StrUtil.h"

bool Game::setType(std::string desc) {
  if (desc == "Blokus Duo") {
    restart(Board::T_DUO);
    return true;
  } else if (desc == "Blokus") {
    restart(Board::T_CLASSIC);
    return true;
  } else {
    return false;
  }
}

void Game::restart() {
  restart(board.type);
}

void Game::restart(int boardType) {
  board.init(boardType);
}

std::string Game::findMove(int player) {
  clock.start();
  SearchResult sr = minimax(player, 2);
  board.makeMove(player, sr.move);
  std::string str = StrUtil::moveToString(sr.move.mask, board.getSize());
  clock.stop();

  return str;
}

SearchResult Game::minimax(int player, int depth) {
  SearchResult best;
  if (depth == 0) {
    best.score = board.eval();
    return best;
  }

  MoveGenerator gen(board);
  gen.run(player);

  if (!gen.size) {
    best.score = board.eval();
    return best;
  }
  player = gen.player; // not necessarily the same

  best = SearchResult::minusInfinity();

  for (int i = 0; i < gen.size; i++) {
    Move& mv = gen.moves[i];
    board.makeMove(player, mv);
    SearchResult sr = minimax((player + 1) % board.getNumPlayers(), depth - 1);
    if (sr.score.val[player] > best.score.val[player]) {
      best = { mv, sr.score };
    }
    board.undoMove(player, mv);
  }

  return best;
}

void Game::makeMove(int player, std::string move) {
  Move m;
  m.mask = StrUtil::stringToMove(move, board.getSize());
  m.piece = board.getPieceFromMask(m.mask);
  board.makeMove(player, m);
}
