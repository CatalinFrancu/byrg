#pragma once

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

const int BOARD_SIZE = 14;
const int PADDED_BOARD_SIZE = 16;
const int NUM_PIECES = 21;
const int MAX_PIECE_SIZE = 5;

const int MAX_STONES = 50; // TBD what is realistic

// all rotations, mirrors and shifts of all pieces
const int MAX_PIECE_VARIANTS = 8;
const int MAX_VARIANTS = 14'000; // determined experimentally

const int INFINITY = 2'000'000'000;
