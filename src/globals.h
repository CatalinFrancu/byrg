#pragma once

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

const int BOARD_SIZE = 14;
const int NUM_BITS = BOARD_SIZE * BOARD_SIZE;
const int NUM_PIECES = 21;
const int MAX_PIECE_SIZE = 5;

const int MAX_VARIANTS = 8; // rotations and mirrors of a piece

const int INFINITY = 2'000'000'000;
