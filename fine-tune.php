<?php

const PATH_TO_TWOGTP = '/home/cata/Desktop/pentobi/twogtp/twogtp';
const PATH_TO_PENTOBI = '/home/cata/Desktop/pentobi/pentobi_gtp/pentobi-gtp';
const PATH_TO_BYRG = __DIR__ . '/byrg';

const NUM_GAMES = 100;
const STEP = 2;

$bestDiff = -1000;

for ($pieces = 0; $pieces <= 10; $pieces += STEP) {
  for ($corners = 0; $corners <= 10; $corners += STEP) {
    for ($lost = -10; $lost <= 0; $lost += STEP) {
      printf("==== ownPieces=%d oppPieces=%d ownCorners=%d " .
             "oppCorners=%d ownLost=%d oppLost=%d\n",
             $pieces, $pieces, $corners, $corners, $lost, $lost);
      list($avgDiff, $wins, $draws) =
        playMatch($pieces, $pieces, $corners, $corners, $lost, $lost);
      printf("Average diff %.2lf wins %d draws %d\n",
             $avgDiff, $wins, $draws);
      if ($avgDiff > $bestDiff) {
        printf("    NEW BEST\n");
        $bestDiff = $avgDiff;
      }
    }
  }
}

function playMatch(int $ownPieces, int $oppPieces, int $ownCorners,
                   int $oppCorners, int $ownLost, int $oppLost): array {
  $args = sprintf(
    '--score-own-pieces %s ' .
    '--score-opp-pieces %s ' .
    '--score-own-corners %s ' .
    '--score-opp-corners %s ' .
    '--penalty-own-lost %s ' .
    '--penalty-opp-lost %s ',
    $ownPieces, $oppPieces, $ownCorners, $oppCorners, $ownLost, $oppLost);
  $pipe = 'grep Final | cut -d " " -f 3,4';
  $cmd = sprintf(
    '%s --black "%s %s" --white "%s --nobook --noresign" -g duo 2>&1 | %s',
    PATH_TO_TWOGTP,
    PATH_TO_BYRG,
    $args,
    PATH_TO_PENTOBI,
    $pipe
  );

  $diff = 0;
  $wins = 0;
  $draws = 0;
  for ($g = 0; $g < NUM_GAMES; $g++) {
    list($black, $white) = playGame($cmd);
    // printf("black %d white %d diff %d\n", $black, $white, $black - $white);
    $diff += $black - $white;
    $wins += ($black > $white);
    $draws += ($black == $white);
  }
  return [ $diff / NUM_GAMES, $wins, $draws ];
}

function playGame(string $cmd): array {
  @unlink('output.blksgf');
  @unlink('output.dat');

  $output = null;
  exec($cmd, $output);
  return explode(' ', $output[0]);
}
