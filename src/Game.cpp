#include "Args.h"
#include <assert.h>
#include "Game.h"
#include "MoveGenerator.h"
#include "Rng.h"
#include <string>
#include "StrUtil.h"
#include "UndoInfo.h"
#include <vector>

Game::Game(Args& args): args(args) {
  pieceSet.precompute();
  board.pieceSet = &pieceSet;
  if (args.seed != Args::NONE) {
    Rng::init(args.seed);
  }
}

bool Game::setType(std::string desc) {
  return (desc == "Blokus Duo");
}

void Game::restart() {
  board.init(args);
}

std::string Game::findMove(int player) {
  clock.start();
  posCount = moveCount = 0;

  // Take the arbiter's word that @player is the side to move and there are
  // legal moves.
  board.setPlayer(player);
  Move move;
  int score;
  int depth = getDepth();
  alphaBetaWrapper(depth, move, score);
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

int Game::getDepth() {
  int mask = board.inHand[board.stm];
  int played = NUM_PIECES - __builtin_popcount(mask);
  int depth = (played < OPENING_MOVES) ? DEPTH_OPENING : DEPTH_REST;
  fprintf(stderr, "%d pieces played, calling alpha-beta at depth %d\n",
          played, depth);
  return depth;
}

std::vector<Move> Game::randomizeMoves() {
  std::vector<Move> moves;
  MoveGenerator gen(board);
  while (!gen.isFinished()) {
    moves.push_back(gen.getMove());
  }

  for (unsigned i = 0; i < moves.size(); i++) {
    int j = Rng::get() % (i + 1);
    Move tmp = moves[i];
    moves[i] = moves[j];
    moves[j] = tmp;
  }

  return moves;
}

void Game::alphaBetaWrapper(int depth, Move& move, int& score) {
  move.setPass();
  score = -(INFINITY+1); // even losing positions beat this

  std::vector<Move> moves = randomizeMoves();

  for (Move mv: moves) {
    moveCount++;
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
  int x = board.getScore(0), y = board.getScore(1);
  fprintf(stderr, "Final score: %d %d diff %d\n", x, y, x - y);
}
