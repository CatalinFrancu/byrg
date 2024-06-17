#include "assert.h"
#include "Bitmap.h"
#include "Board.h"
#include "globals.h"
#include "MoveList.h"
#include "Piece.h"

const int Board::SIZES[Board::NUM_TYPES] = { 14, 20 };
const int Board::NUM_PLAYERS[Board::NUM_TYPES] = { 2, 4 };
const int Board::STARTING_POSITIONS[Board::NUM_TYPES][MAX_PLAYERS] = {
  { 130, 65 },
  { 380, 399, 19, 0 },
};

bitset Board::firstRank;
bitset Board::lastRank;
bitset Board::firstFile;
bitset Board::lastFile;

int Board::getSize() {
  return SIZES[type];
}

int Board::getNumPlayers() {
  return NUM_PLAYERS[type];
}

void Board::init(int type) {
  this->type = type;
  initBorderMasks();
  initPlayerMasks();
  initPieces();
}

void Board::initBorderMasks() {
  int size = getSize();
  for (int i = 0; i < size; i++) {
    firstRank.set(i);
    lastRank.set(size * (size - 1) + i);
    firstFile.set(size * i);
    lastFile.set(size * i + size - 1);
  }
}

void Board::initPlayerMasks() {
  for (int i = 0; i < getNumPlayers(); i++) {
    occ[i] = 0;
    inHand[i] = (1 << NUM_PIECES) - 1;
  }
}

void Board::initPieces() {
  Bitmap bitmap;
  for (int i = 0; i < NUM_PIECES; i++) {
    pieces[i].numVariants = 0;
    bitmap.copyFrom(BITMAPS[i]);
    for (int mir = 0; mir < 2; mir++) {
      for (int rot = 0; rot < 4; rot++) {
        pieces[i].considerBitmap(bitmap, getSize());
        bitmap.rotate();
      }
      bitmap.mirror();
    }
  }
}

Score Board::eval() {
  Score score;
  for (int i = 0; i < getNumPlayers(); i++) {
    bitset unavailable;
    bitset stones;
    makeLandscape(i, unavailable, stones);
    score.val[i] =
      occ[i].count() * COEF_POP +
      stones.count() * COEF_STONES;
  }
  return score;
}

void Board::genMoves(int player, MoveList& dest) {
  int inactivePlayers = 0;
  dest.size = 0;

  while (!dest.size && inactivePlayers < getNumPlayers()) {
    bitset unavailable;
    bitset stones;
    makeLandscape(player, unavailable, stones);

    int hand = inHand[player];
    while (hand) {
      int piece = __builtin_ctz(hand);
      for (int rot = 0; rot < pieces[piece].numVariants; rot++) {
        genMovesWithPiece(player, piece, rot, unavailable, stones, dest);
      }
      hand &= hand - 1;
    }

    dest.player = player;
    player = (player + 1) % getNumPlayers();
    inactivePlayers++;
  }
}

void Board::makeLandscape(int player, bitset& unavailable, bitset& stones) {
  unavailable.reset();
  bitset& me = occ[player];
  int size = getSize();
  int np = getNumPlayers();

  // Squares occupied by any player are unavailable.
  for (int i = 0; i < np; i++) {
    unavailable |= occ[i];
  }

  // Squares adjacent to my pieces are unavailable.
  unavailable |= (me & ~firstRank) >> size;
  unavailable |= (me & ~lastRank) << size;
  unavailable |= (me & ~firstFile) >> 1;
  unavailable |= (me & ~lastFile) << 1;

  // The piece must touch a stepping stone.
  if (me.any()) {
    stones =
      ((me & ~firstRank & ~firstFile) >> (size + 1)) |
      ((me & ~firstRank & ~lastFile) >> (size - 1)) |
      ((me & ~lastRank & ~firstFile) << (size - 1)) |
      ((me & ~lastRank & ~lastFile) << (size + 1));
  } else {
    stones = getStartingPos(player);
  }
}

bitset Board::getStartingPos(int player) {
  bitset result(0);
  int pos = STARTING_POSITIONS[type][player];
  result[pos] = true;
  return result;
}

void Board::genMovesWithPiece(int player, int piece, int rot, bitset& unavailable,
                              bitset& stones, MoveList& dest) {
  bitset& orig = pieces[piece].variants[rot].mask;

  bool rankOverflow = false;
  int rank = 0;
  while (!rankOverflow) {
    bitset mask = orig << (rank * getSize());
    tryMove(piece, mask, unavailable, stones, dest);

    bool fileOverflow = false;
    int file = 0;
    while (!fileOverflow) {
      mask <<= 1;

      tryMove(piece, mask, unavailable, stones, dest);

      file++;
      fileOverflow = (mask & lastFile).any();
    }

    rank++;
    rankOverflow = (mask & lastRank).any();
  }
}

void Board::tryMove(int piece, bitset& mask, bitset& unavailable,
                    bitset& stones, MoveList& dest) {
  if ((mask & stones).any() && (mask & unavailable).none()) {
    dest.add(mask, piece);
  }
}

void Board::makeMove(int player, Move& move) {
  occ[player] ^= move.mask;
  inHand[player] ^= (1 << move.piece);
}

void Board::undoMove(int player, Move& move) {
  // Identical, under the current board representation.
  makeMove(player, move);
}

int Board::getPieceFromMask(bitset mask) {
  // Shift the mask towards the LSB
  while ((mask & firstRank).none()) {
    mask >>= getSize();
  }
  while ((mask & firstFile).none()) {
    mask >>= 1;
  }

  for (int p = 0; p < NUM_PIECES; p++) {
    for (int rot = 0; rot < pieces[p].numVariants; rot++) {
      if (pieces[p].variants[rot].mask == mask) {
        return p;
      }
    }
  }
  assert(false);
}

void Board::print() {
  int size = getSize();
  for (int rank = size - 1; rank >= 0; rank--) {
    printf("%2d ", rank + 1);
    for (int file = 0; file < size; file++) {
      int bit = rank * size + file;
      printBit(bit);
    }
    printf("\n");
  }

  printf("   ");
  for (int file = 0; file < size; file++) {
    printf(" %c", file + 'a');
  }
  printf("\n");
}

void Board::printBit(int bit) {
  int p = 0;
  while ((p < getNumPlayers()) && !occ[p][bit]) {
    p++;
  }

  if (p == getNumPlayers()) {
    printf("  ");
  } else {
    printf("%s  %s", ANSI_COLORS[p], DEFAULT_COLOR);
  }
}
