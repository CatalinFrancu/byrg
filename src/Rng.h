#pragma once

class Rng {
public:
  static void init(unsigned seed);
  static int get();
};
