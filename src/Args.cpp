#include "Args.h"
#include <getopt.h>
#include <stdlib.h>

Args::Args(int argc, char** argv) {
  int index;
  while (!getopt_long(argc, argv, "", OPTIONS, &index)) {
    int val = atoi(optarg);
    switch (index) {
      case 0: scoreOwnPieces = val; break;
      case 1: scoreOppPieces = val; break;
      case 2: scoreOwnCorners = val; break;
      case 3: scoreOppCorners = val; break;
      case 4: penaltyOwnLost = val; break;
      case 5: penaltyOppLost = val; break;
      case 6: seed = val; break;
    }
  }
}
