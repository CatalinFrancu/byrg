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
  int result = SCORE_SELF * playerEval(player)
    - SCORE_OPP * playerEval(1 - player);
  // int result = SCORE_OPP * sumStoneDist(1 - player) -
  //   SCORE_SELF * sumStoneDist(player);
  return result;
}

int Board::playerEval(int player) {
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

int Board::sumStoneDist(int player) {
  bfsInit(player);
  bfs(player);
  return bfsCollect(player);
}

void Board::bfsInit(int player) {
  for (int r = 0; r < PADDED_BOARD_SIZE; r++) {
    for (int c = 0; c < PADDED_BOARD_SIZE; c++) {
      dist[r][c] = MAX_DIST;
    }
  }
  head = 0;
  tail = collectStones(player, queue);
  for (int i = 0; i < tail; i++) {
    dist[queue[i].r][queue[i].c] = 0;
  }
}

void Board::bfs(int player) {
  while (head != tail) {
    Cell cell = queue[head++];
    int d = dist[cell.r][cell.c];
    bfsExtend(player, cell.r - 1, cell.c, d + 1);
    bfsExtend(player, cell.r, cell.c - 1, d + 1);
    bfsExtend(player, cell.r + 1, cell.c, d + 1);
    bfsExtend(player, cell.r, cell.c + 1, d + 1);
  }
}

void Board::bfsExtend(int player, u8 r, u8 c, int d) {
  if ((dist[r][c] == MAX_DIST) &&
      isAvailable(player, r, c)) {
    dist[r][c] = d;
    queue[tail++] = { r, c };
  }
}

int Board::bfsCollect(int player) {
  int result = 0;

  for (int r = 1; r <= BOARD_SIZE; r++) {
    for (int c = 1; c <= BOARD_SIZE; c++) {
      if (isAvailable(player, r, c)) {
        if (dist[r][c] == MAX_DIST) {
          result += MAX_DIST;
        } else {
          result += (int)dist[r][c] * dist[r][c];
        }
      } else if (a[r][c] == EMPTY) {
        result += SCORE_DEAD;
      }
    }
  }

  return result;
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
