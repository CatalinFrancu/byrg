#include "Board.h"
#include "MoveGenerator.h"
#include <stdio.h>

MoveGenerator::MoveGenerator(Board& b, int player):
  board(b),
  player(player) {
  numMoves = 0;
}

void MoveGenerator::run() {
  runForPlayer();
  if (!numMoves) {
    player = 1 - player;
    runForPlayer();
  }
}

void MoveGenerator::runForPlayer() {
  Bitset stones;
  board.makeLandscape(player, unavailable, stones);

  int stone;
  while ((stone = stones.consumeBit()) != Bitset::NONE) {
    runForPlayerStone(stone);
  }
}

void MoveGenerator::runForPlayerStone(int stone) {
  int hand = board.inHand[player];
  while (hand) {
    int piece = __builtin_ctz(hand);
    int numShifts = board.pieceSet->numShifts[piece][stone];
    for (int i = 0; i < numShifts; i++) {
      runForPlayerStoneShift(piece, stone, i);
    }
    hand &= hand - 1;
  }
}

void MoveGenerator::runForPlayerStoneShift(int piece, int stone, int shift) {
  Bitset& b = board.pieceSet->shiftedMasks[piece][stone][shift];

  if ((b & unavailable).none()) {
    moves[numMoves++] = { b, (u8)piece };
  }
}
