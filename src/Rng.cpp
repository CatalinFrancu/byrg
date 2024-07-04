#include "Rng.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void Rng::init(unsigned seed) {
  if (seed == 0) {
    struct timeval time;
    gettimeofday(&time, NULL);
    seed = time.tv_sec * 1'000'000 + time.tv_usec;
  }

  srand(seed);
  fprintf(stderr, "Initialized random seed to %d\n", seed);
}

int Rng::get() {
  return rand();
}
