#include "Bitset.h"
#include <stdio.h>
#include <string.h>

void Bitset::set(int pos) {
  buf[pos / 64] |= (1ull << (pos % 64));
}

bool Bitset::get(int pos) {
  return (buf[pos / 64] >> (pos % 64)) & 1;
}

int Bitset::count() {
  int res = 0;
  for (int i = 0; i <= WHOLE; i++) {
    res += __builtin_popcountll(buf[i]);
  }
  return res;
}

bool Bitset::any() {
  return count() > 0;
}

bool Bitset::none() {
  return count() == 0;
}

void Bitset::clear() {
  memset(buf, 0, sizeof(buf));
}

int Bitset::consumeBit() {
  int pos = 0;
  while ((pos <= WHOLE) && !buf[pos]) {
    pos++;
  }

  if (pos > WHOLE) {
    return NONE;
  }

  int ret = 64 * pos + __builtin_ctzll(buf[pos]);
  buf[pos] &= buf[pos] - 1;
  return ret;
}

bool Bitset::operator==(Bitset other) {
  int i = 0;
  while ((i < WHOLE) && (buf[i] == other.buf[i])) {
    i++;
  }
  return (buf[i] == other.buf[i]);
}

Bitset Bitset::operator&(Bitset other) {
  Bitset res;
  for (int i = 0; i <= WHOLE; i++) {
    res.buf[i] = buf[i] & other.buf[i];
  }
  return res;
}

Bitset Bitset::operator|(Bitset other) {
  Bitset res;
  for (int i = 0; i <= WHOLE; i++) {
    res.buf[i] = buf[i] | other.buf[i];
  }
  return res;
}

void Bitset::operator|=(Bitset other) {
  for (int i = 0; i <= WHOLE; i++) {
    buf[i] |= other.buf[i];
  }
}

void Bitset::operator^=(Bitset other) {
  for (int i = 0; i <= WHOLE; i++) {
    buf[i] ^= other.buf[i];
  }
}

Bitset Bitset::operator~() {
  Bitset res;
  for (int i = 0; i < WHOLE; i++) {
    res.buf[i] = ~buf[i];
  }
  res.buf[WHOLE] = buf[WHOLE] ^ ((1ull << PART) - 1);
  return res;
}

Bitset Bitset::operator>>(int dist) {
  Bitset res;
  res.copyFrom(this);
  res >>= dist;
  return res;
}

void Bitset::operator>>=(int dist) {
  if (dist % 64) {
    int pos = 0;
    int word = dist / 64;
    int rest = dist % 64;
    while (word < WHOLE) {
      buf[pos++] = (buf[word + 1] << (64 - rest)) | (buf[word] >> rest);
      word++;
    }
    buf[pos++] = buf[WHOLE] >> rest;
    while (pos <= WHOLE) {
      buf[pos++] = 0;
    }
  } else {
    dist /= 64;
    for (int pos = 0; pos <= WHOLE - dist; pos++) {
      buf[pos] = buf[pos + dist];
    }
    for (int pos = WHOLE - dist + 1; pos <= WHOLE; pos++) {
      buf[pos] = 0;
    }
  }
}

Bitset Bitset::operator<<(int dist) {
  Bitset res;
  res.copyFrom(this);
  res <<= dist;
  return res;
}

void Bitset::operator<<=(int dist) {
  if (dist % 64) {
    int pos = WHOLE;
    int word = WHOLE - dist/64;
    int rest = dist % 64;
    while (word > 0) {
      buf[pos--] = (buf[word] << rest) | (buf[word - 1] >> (64 - rest));
      word--;
    }
    buf[pos--] = buf[0] << rest;
    while (pos >= 0) {
      buf[pos--] = 0;
    }
  } else {
    dist /= 64;
    for (int pos = WHOLE; pos >= dist; pos--) {
      buf[pos] = buf[pos - dist];
    }
    for (int pos = dist - 1; pos >= 0; pos--) {
      buf[pos] = 0;
    }
  }
}

void Bitset::copyFrom(const Bitset* src) {
  for (int i = 0; i <= WHOLE; i++) {
    buf[i] = src->buf[i];
  }
}

void Bitset::print(int width) {
  int rows = (NUM_BITS - 1) / width + 1;
  for (int r = rows - 1; r >= 0; r--) {
    for (int b = r * width;
         (b < (r + 1) * width) && (b < NUM_BITS);
         b++) {
      putchar(get(b) ? '*' : '.');
    }
    putchar('\n');
  }
  putchar('\n');
}
