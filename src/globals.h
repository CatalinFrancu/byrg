#pragma once

typedef unsigned char u8;
typedef unsigned long long u64;

const int BOARD_SIZE = 14;
const int PADDED_BOARD_SIZE = 16;
const int NUM_PIECES = 21;
const int MAX_PIECE_SIZE = 5;

const int MAX_STONES = 50; // TBD what is realistic

// all rotations, mirrors and shifts of all pieces
const int MAX_PIECE_VARIANTS = 8;
const int MAX_VARIANTS = 200'000;
