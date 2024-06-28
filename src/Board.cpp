#include "assert.h"
#include "Bitmap.h"
#include "Board.h"
#include "globals.h"
#include "Math.h"
#include "PieceSet.h"
#include <stdio.h>
#include "UndoInfo.h"

void Board::init() {
  initMatrix();
  initPlayers();
}

void Board::initMatrix() {
  for (int i = 0; i < PADDED_BOARD_SIZE; i++) {
    for (int j = 0; j < PADDED_BOARD_SIZE; j++) {
      a[i][j] = EMPTY;
    }
  }
  count[0] = count[1] = 0;
  count[EMPTY] = PADDED_BOARD_SIZE * PADDED_BOARD_SIZE;
}

void Board::initPlayers() {
  inHand[0] = inHand[1] = (1 << NUM_PIECES) - 1;
  corners[0].init(STARTING_POSITIONS[0]);
  corners[1].init(STARTING_POSITIONS[1]);
  setPlayer(0);
}

void Board::setPlayer(int player) {
  stm = player;
  passCount = 0;
}

int Board::getScore(int player) {
  int s = count[player];
  if (!inHand[player]) {
    s += NO_HAND_BONUS;
  }
  return s;
}

bool Board::isFinal() {
  return passCount == 2;
}

int Board::eval() {
  if (isFinal()) {
    int diff = count[stm] - count[1 - stm];
    return INFINITY * Math::sgn(diff);
  }
  return SCORE_OWN_PIECES * count[stm]
    + SCORE_OWN_CORNERS * corners[stm].size
    - SCORE_OPP_PIECES * count[1 - stm]
    - SCORE_OPP_CORNERS * corners[1 - stm].size;
}

void Board::setArea(Piece& piece, int val) {
  for (int i = 0; i < piece.size; i++) {
    int rank = piece.cells[i].rank;
    int file = piece.cells[i].file;
    count[a[rank][file]]--;
    a[rank][file] = val;
    count[val]++;
  }
}

void Board::updateCornerLists(Piece& piece, UndoInfo* undo) {
  // Both players lose access to cells effectively occupied.
  for (int i = 0; i < piece.size; i++) {
    corners[0].remove(piece.cells[i], undo[0]);
    corners[1].remove(piece.cells[i], undo[1]);
  }

  // Active player also loses access to neighboring cells.
  for (int i = 0; i < piece.numNeighbors; i++) {
    corners[stm].remove(piece.neighbors[i], undo[stm]);
  }

  // Active player also gains access to unoccupied corners.
  for (int i = 0; i < piece.numCorners; i++) {
    Cell c = piece.corners[i];
    if (a[(int)c.rank][(int)c.file] == EMPTY) {
      corners[stm].add(c, undo[stm]);
    }
  }
}

void Board::makeMove(Move& move) {
  UndoInfo ignored[2];
  makeMove(move, ignored);
}

void Board::makeMove(Move& move, UndoInfo* undo) {
  if (move.isPass()) {
    passCount++;
  } else {
    passCount = 0;
    Piece p = pieceSet->variants[move.varId];
    setArea(p, stm);
    inHand[stm] ^= (1 << move.pieceId);
    updateCornerLists(p, undo);
  }
  stm = 1 - stm;
}

void Board::undoMove(Move& move, UndoInfo* undo) {
  stm = 1 - stm;
  if (move.isPass()) {
    passCount--;
  } else {
    passCount = 0;
    Piece p = pieceSet->variants[move.varId];
    setArea(p, EMPTY);
    inHand[stm] ^= (1 << move.pieceId);
    corners[0].restore(undo[0]);
    corners[1].restore(undo[1]);
  }
}

bool Board::accommodates(Piece p) {
  for (int i = 0; i < p.size; i++) {
    Cell c = p.cells[i];
    if (a[(int)c.rank][(int)c.file] != EMPTY) {
      return false;
    }
  }
  for (int i = 0; i < p.numNeighbors; i++) {
    Cell c = p.neighbors[i];
    if (a[(int)c.rank][(int)c.file] == stm) {
      return false;
    }
  }
  return true;
}

void Board::print() {
  for (int rank = BOARD_SIZE; rank >= 1; rank--) {
    fprintf(stderr, "%2d ", rank);
    for (int file = 1; file <= BOARD_SIZE; file++) {
      printCell(rank, file);
    }
    fprintf(stderr, "\n");
  }

  fprintf(stderr, "   ");
  for (int file = 0; file < BOARD_SIZE; file++) {
    fprintf(stderr, " %c", file + 'a');
  }
  fprintf(stderr, "\n");
}

void Board::printCell(int rank, int file) {
  if (a[rank][file] == EMPTY) {
    fprintf(stderr, "  ");
  } else {
    int p = a[rank][file];
    fprintf(stderr, "%s  %s", ANSI_COLORS[p], DEFAULT_COLOR);
  }
}
