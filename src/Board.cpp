#include "assert.h"
#include "Bitmap.h"
#include "Board.h"
#include "globals.h"
#include "PieceSet.h"
#include <stdio.h>

void Board::init() {
  initMatrix();
  initPlayerMasks();
}

void Board::initMatrix() {
  for (int i = 0; i < PADDED_BOARD_SIZE; i++) {
    for (int j = 0; j < PADDED_BOARD_SIZE; j++) {
      a[i][j] = EMPTY;
    }
  }
}

void Board::initPlayerMasks() {
  inHand[0] = inHand[1] = (1 << NUM_PIECES) - 1;
}

int Board::eval(int player) {
  return SCORE_SELF * sideEval(player)
    - SCORE_OPP * sideEval(1 - player);
}

int Board::sideEval(int player) {
  // count stones and cells
  int numStones = 0;
  int numCells = 0;
  for (u8 r = 1; r <= BOARD_SIZE; r++) {
    for (u8 c = 1; c <= BOARD_SIZE; c++) {
      if (isAvailable(player, r, c) &&
          ((a[r - 1][c - 1] == player) ||
           (a[r - 1][c + 1] == player) ||
           (a[r + 1][c - 1] == player) ||
           (a[r + 1][c + 1] == player))) {
        numStones++;
      }
      if (a[r][c] == player) {
        numCells++;
      }
    }
  }

  if (!numStones) {
    numStones = 1;
  }

  int score = numStones + numCells * SCORE_LARGE_PIECES;
  return score;
}

void Board::setArea(int val, Move& move) {
  PieceVariant var = pieceSet->variants[move.variant];
  for (int i = 0; i < var.size; i++) {
    int row = var.cells[i] / PADDED_BOARD_SIZE;
    int col = var.cells[i] % PADDED_BOARD_SIZE;
    a[row][col] = val;
  }
}

void Board::makeMove(int player, Move& move) {
  setArea(player, move);
  inHand[player] ^= (1 << move.piece);
}

void Board::undoMove(int player, Move& move) {
  setArea(EMPTY, move);
  inHand[player] ^= (1 << move.piece);
}

int Board::collectStones(int player, Cell* dest) {
  int n = 0;
  for (u8 r = 1; r <= BOARD_SIZE; r++) {
    for (u8 c = 1; c <= BOARD_SIZE; c++) {
      if (isAvailable(player, r, c) &&
          ((a[r - 1][c - 1] == player) ||
           (a[r - 1][c + 1] == player) ||
           (a[r + 1][c - 1] == player) ||
           (a[r + 1][c + 1] == player))) {
        dest[n++] = { r, c };
      }
    }
  }

  if (!n) {
    dest[n++] = STARTING_POSITIONS[player];
  }
  return n;
}

bool Board::accommodates(PieceVariant var, int player) {
  for (int i = 0; i < var.size; i++) {
    int rank = var.cells[i] / PADDED_BOARD_SIZE;
    int file = var.cells[i] % PADDED_BOARD_SIZE;
    if (!isAvailable(player, rank, file)) {
      return false;
    }
  }
  return true;
}

bool Board::isAvailable(int player, int rank, int file) {
  return
    (rank >= 0) && (rank < PADDED_BOARD_SIZE) &&
    (file >= 0) && (file < PADDED_BOARD_SIZE) &&
    (a[rank][file] == EMPTY) &&
    (a[rank][file - 1] != player) &&
    (a[rank - 1][file] != player) &&
    (a[rank][file + 1] != player) &&
    (a[rank + 1][file] != player);
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
