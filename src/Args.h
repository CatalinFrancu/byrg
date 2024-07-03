#pragma once

#include <getopt.h>
#include "globals.h"

class Args {
public:
  static const int NONE = INFINITY;
  Args(int argc, char** argv);

  int scoreOwnPieces = NONE;
  int scoreOppPieces = NONE;
  int scoreOwnCorners = NONE;
  int scoreOppCorners = NONE;
  int penaltyOwnLost = NONE;
  int penaltyOppLost = NONE;

private:
  static constexpr struct option OPTIONS[] = {
    { "score-own-pieces",  required_argument, 0,  0 },
    { "score-opp-pieces",  required_argument, 0,  0 },
    { "score-own-corners", required_argument, 0,  0 },
    { "score-opp-corners", required_argument, 0,  0 },
    { "penalty-own-lost",  required_argument, 0,  0 },
    { "penalty-opp-lost",  required_argument, 0,  0 },
    { 0,                   0,                 0,  0 },
  };

};
