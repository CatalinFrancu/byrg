#include "Bitset.h"
#include <stdio.h>
#include <string.h>

int Bitset::size;
int Bitset::whole;
int Bitset::part;

void Bitset::setSize(int size) {
  Bitset::size = size;
  whole = size / 64;
  part = size % 64;
}

void Bitset::set(int pos) {
  buf[pos / 64] |= (1ull << (pos % 64));
}

bool Bitset::get(int pos) {
  return (buf[pos / 64] >> (pos % 64)) & 1;
}

int Bitset::count() {
  int res = 0;
  for (int i = 0; i <= whole; i++) {
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

bool Bitset::operator==(Bitset other) {
  int i = 0;
  while ((i < whole) && (buf[i] == other.buf[i])) {
    i++;
  }
  return (buf[i] == other.buf[i]);
}

Bitset Bitset::operator&(Bitset other) {
  Bitset res;
  for (int i = 0; i <= whole; i++) {
    res.buf[i] = buf[i] & other.buf[i];
  }
  return res;
}

Bitset Bitset::operator|(Bitset other) {
  Bitset res;
  for (int i = 0; i <= whole; i++) {
    res.buf[i] = buf[i] | other.buf[i];
  }
  return res;
}

void Bitset::operator|=(Bitset other) {
  for (int i = 0; i <= whole; i++) {
    buf[i] |= other.buf[i];
  }
}

void Bitset::operator^=(Bitset other) {
  for (int i = 0; i <= whole; i++) {
    buf[i] ^= other.buf[i];
  }
}

Bitset Bitset::operator~() {
  Bitset res;
  int whole = size / 64;
  for (int i = 0; i < whole; i++) {
    res.buf[i] = ~buf[i];
  }
  res.buf[whole] = buf[whole] ^ ((1ull << part) - 1);
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
    while (word < whole) {
      buf[pos++] = (buf[word + 1] << (64 - rest)) | (buf[word] >> rest);
      word++;
    }
    buf[pos++] = buf[whole] >> rest;
    while (pos <= whole) {
      buf[pos++] = 0;
    }
  } else {
    dist /= 64;
    for (int pos = 0; pos <= whole - dist; pos++) {
      buf[pos] = buf[pos + dist];
    }
    for (int pos = whole - dist + 1; pos <= whole; pos++) {
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
    int pos = whole;
    int word = whole - dist/64;
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
    for (int pos = whole; pos >= dist; pos--) {
      buf[pos] = buf[pos - dist];
    }
    for (int pos = dist - 1; pos >= 0; pos--) {
      buf[pos] = 0;
    }
  }
}

void Bitset::copyFrom(const Bitset* src) {
  for (int i = 0; i <= whole; i++) {
    buf[i] = src->buf[i];
  }
}

void Bitset::print(int width) {
  int rows = (size - 1) / width + 1;
  for (int r = rows - 1; r >= 0; r--) {
    for (int b = r * width;
         (b < (r + 1) * width) && (b < size);
         b++) {
      putchar(get(b) ? '*' : '.');
    }
    putchar('\n');
  }
  putchar('\n');
}
