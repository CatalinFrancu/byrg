#pragma once

#include <bitset>

const int MAX_CELLS = 400;

typedef unsigned char u8;
typedef std::bitset<MAX_CELLS> bitset;

const int MAX_PLAYERS = 4;
const int NUM_PIECES = 21;
const int MAX_VARIANTS = 8; // rotations and mirrors of a piece
const int MAX_PIECE_SIZE = 5;
