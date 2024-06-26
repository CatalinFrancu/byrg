#include "assert.h"
#include "Bitmap.h"
#include "Board.h"
#include "globals.h"
#include "PieceSet.h"
#include <stdio.h>
#include "UndoInfo.h"

void Board::init() {
  initMatrix();
  initPlayerMasks();
  initCornerLists();
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

void Board::initPlayerMasks() {
  inHand[0] = inHand[1] = (1 << NUM_PIECES) - 1;
}

void Board::initCornerLists() {
  corners[0].init(STARTING_POSITIONS[0]);
  corners[1].init(STARTING_POSITIONS[1]);
}

int Board::getScore(int player) {
  int s = count[player];
  if (!inHand[player]) {
    s += NO_HAND_BONUS;
  }
  return s;
}

int Board::eval(int player) {
  return SCORE_OWN_PIECES * count[player]
    + SCORE_OWN_CORNERS * corners[player].size
    - SCORE_OPP_PIECES * count[1 - player]
    - SCORE_OPP_CORNERS * corners[1 - player].size;
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

void Board::updateCornerLists(int player, Piece& piece, UndoInfo* undo) {
  // Both players lose access to cells effectively occupied.
  for (int i = 0; i < piece.size; i++) {
    corners[0].remove(piece.cells[i], undo[0]);
    corners[1].remove(piece.cells[i], undo[1]);
  }

  // Active player also loses access to neighboring cells.
  for (int i = 0; i < piece.numNeighbors; i++) {
    corners[player].remove(piece.neighbors[i], undo[player]);
  }

  // Active player also gains access to unoccupied corners.
  for (int i = 0; i < piece.numCorners; i++) {
    Cell c = piece.corners[i];
    if (a[c.rank][c.file] == EMPTY) {
      corners[player].add(c, undo[player]);
    }
  }
}

void Board::undoCornerLists(int player, UndoInfo* undo) {
  corners[0].restore(undo[0]);
  corners[1].restore(undo[1]);
}

void Board::makeMove(int player, Move& move) {
  UndoInfo ignored[2];
  makeMove(player, move, ignored);
}

void Board::makeMove(int player, Move& move, UndoInfo* undo) {
  Piece p = pieceSet->variants[move.varId];
  setArea(p, player);
  inHand[player] ^= (1 << move.pieceId);
  updateCornerLists(player, p, undo);
}

void Board::undoMove(int player, Move& move, UndoInfo* undo) {
  Piece p = pieceSet->variants[move.varId];
  setArea(p, EMPTY);
  inHand[player] ^= (1 << move.pieceId);
  undoCornerLists(player, undo);
}

bool Board::accommodates(Piece p, int player) {
  for (int i = 0; i < p.size; i++) {
    Cell c = p.cells[i];
    if (a[c.rank][c.file] != EMPTY) {
      return false;
    }
  }
  for (int i = 0; i < p.numNeighbors; i++) {
    Cell c = p.neighbors[i];
    if (a[c.rank][c.file] == player) {
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
