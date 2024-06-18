#include "Board.h"
#include "MoveGenerator.h"

MoveGenerator::MoveGenerator(Board& b): board(b) {
  size = 0;
}

void MoveGenerator::run(int player) {
  int inactivePlayers = 0;

  while (!size && inactivePlayers < board.getNumPlayers()) {
    Bitset stones;
    board.makeLandscape(player, unavailable, stones);

    int hand = board.inHand[player];
    while (hand) {
      int piece = __builtin_ctz(hand);
      for (int rot = 0; rot < board.pieces[piece].numVariants; rot++) {
        genMovesWithPiece(player, piece, rot, stones);
      }
      hand &= hand - 1;
    }

    this->player = player;
    player = (player + 1) % board.getNumPlayers();
    inactivePlayers++;
  }
}

void MoveGenerator::genMovesWithPiece(int player, int piece, int rot, Bitset& stones) {
  Bitset& orig = board.pieces[piece].variants[rot].mask;

  bool rankOverflow = false;
  int rank = 0;
  while (!rankOverflow) {
    Bitset mask = orig << (rank * board.getSize());
    tryMove(piece, mask, stones);

    bool fileOverflow = false;
    int file = 0;
    while (!fileOverflow) {
      mask <<= 1;

      tryMove(piece, mask, stones);

      file++;
      fileOverflow = (mask & board.lastFile).any();
    }

    rank++;
    rankOverflow = (mask & board.lastRank).any();
  }
}

void MoveGenerator::tryMove(int piece, Bitset& mask, Bitset& stones) {
  if ((mask & stones).any() && (mask & unavailable).none()) {
    add(mask, piece);
  }
}

void MoveGenerator::add(Bitset& mask, int piece) {
  moves[size].mask = mask;
  moves[size].piece = piece;
  size++;
}
