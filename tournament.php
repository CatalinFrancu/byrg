<?php

const NUM_STAGES = 2; // double round robin

const TWOGTP = '/home/cata/Desktop/pentobi/twogtp/twogtp';
const ENGINE_ROOT = '/home/cata/projects/nerdvana/2023-2024/2024-07-summer-camp/engines/';
const RANDOM_SEED = 199773;
const SAVE_DIR = __DIR__ . '/tournaments/' . RANDOM_SEED . '/';
const LOG_FILE = '/tmp/log.txt';
const SAVE_FILE = 'output.blksgf';
const DAT_FILE = 'output.dat';

const PLAYERS = [
  [
    'name' => 'Ansedra',
    'invocation' => ENGINE_ROOT . 'Blokus-Player/mutare_alpha_beta_final',
  ],
  [
    'name' => 'Bro',
    'invocation' => ENGINE_ROOT . 'Bro-Will-Play-Blokus/Blockus/main',
  ],
  [
    'name' => 'Byrg',
    'invocation' => '/home/cata/projects/byrg/byrg --seed 0',
  ],
  [
    'name' => 'Randoom',
    'invocation' => ENGINE_ROOT . 'randoom2/Blokus',
  ],
  [
    'name' => 'TTCO',
    'invocation' => ENGINE_ROOT . 'ttco/TTCO/main',
  ],
  // [
  //   'name' => 'Pentobi',
  //   'invocation' => '/home/cata/Desktop/pentobi/pentobi_gtp/pentobi-gtp --nobook --noresign',
  // ],
];

$ord = [];
$flip = false;

main();

function main(): void {
  global $ord;
  $ord = genPlayerOrder();
  playTournament();
}

function genPlayerOrder(): array {
  srand(RANDOM_SEED);
  $arr = range(0, getNumPlayers() - 1);
  shuffle($arr);
  return $arr;
}

function getNumPlayers(): int {
  $n = count(PLAYERS);
  $n += $n % 2;
  return $n;
}

function getNumRounds(): int {
  return (getNumPlayers() - 1) * NUM_STAGES;
}

function playTournament(): void {
  for ($stage = 0; $stage < NUM_STAGES; $stage++) {
    printf("======== Stage %d/%d\n", $stage + 1, NUM_STAGES);
    playStage($stage);
  }
}

function playStage(int $stage): void {
  global $flip;

  $numRounds = getNumPlayers() - 1;
  for ($round = 0; $round < $numRounds; $round++) {
    $globalRound = $stage * $numRounds + $round + 1;
    printf("==== Round %d/%d\n", $round + 1, $numRounds);
    playRound($globalRound);
    $flip = !$flip;
    rotatePlayers();
  }
}

function playRound(int $round): void {
  global $ord, $flip;

  $n = getNumPlayers();
  for ($i = 0; $i < $n / 2; $i++) {
    $p1 = $ord[$i];
    $p2 = $ord[$i + $n / 2];
    if ($flip) {
      $tmp = $p1;
      $p1 = $p2;
      $p2 = $tmp;
    }
    printf("%d-%d\n", $p1, $p2);
    if (($p1 < count(PLAYERS)) && ($p2 < count(PLAYERS))) {
      playGame($round, $p1, $p2);
    }
  }
}

function rotatePlayers(): void {
  global $ord;

  $n = getNumPlayers();
  $topRight = $ord[$n / 2 - 1];
  for ($i = $n / 2 - 1; $i >= 1; $i--) {
    $ord[$i] = $ord[$i - 1];
  }
  $ord[1] = $ord[$n / 2];
  for ($i = $n / 2; $i < $n - 1; $i++) {
    $ord[$i] = $ord[$i + 1];
  }
  $ord[$n - 1] = $topRight;
}

function playGame(int $round, int $p1, int $p2): void {
  $name1 = PLAYERS[$p1]['name'];
  $name2 = PLAYERS[$p2]['name'];
  $bin1 = PLAYERS[$p1]['invocation'];
  $bin2 = PLAYERS[$p2]['invocation'];

  if (gameAlreadyPlayed($round, $p1, $p2)) {
    printf("We already have (some) results for %s-%s, skipping...\n",
           $name1, $name2);
    return;
  }

  $cmd = sprintf(
    '%s --black "%s" --white "%s" -g duo >%s 2>&1',
    TWOGTP, $bin1, $bin2, LOG_FILE);

  printf("Launching game %s-%s\n", $name1, $name2);
  printf("    Command: %s\n", $cmd);

  cleanup();
  exec($cmd);
  moveFiles($round, $p1, $p2);
}

function gameAlreadyPlayed(int $round, int $p1, int $p2): bool {
  return
    file_exists(getLogFile($round, $p1, $p2)) ||
    file_exists(getSaveFile($round, $p1, $p2)) ||
    file_exists(getDatFile($round, $p1, $p2));
}

function cleanup(): void {
  @unlink(LOG_FILE);
  @unlink(SAVE_FILE);
  @unlink(DAT_FILE);
}

function moveFiles(int $round, int $p1, int $p2): void {
  $dir = getRoundSaveDir($round);
  @mkdir($dir, 0755, true); // recursive
  @rename(LOG_FILE, getLogFile($round, $p1, $p2));
  @rename(SAVE_FILE, getSaveFile($round, $p1, $p2));
  @rename(DAT_FILE, getDatFile($round, $p1, $p2));
}

function getRoundSaveDir(int $round): string {
  return sprintf("%s%02d", SAVE_DIR, $round);
}

function getLogFile(int $round, int $p1, int $p2): string {
  return getFileNoExtension($round, $p1, $p2) . '.log';
}

function getSaveFile(int $round, int $p1, int $p2): string {
  return getFileNoExtension($round, $p1, $p2) . '.blksgf';
}

function getDatFile(int $round, int $p1, int $p2): string {
  return getFileNoExtension($round, $p1, $p2) . '.dat';
}

function getFileNoExtension(int $round, int $p1, int $p2): string {
  $dir = getRoundSaveDir($round);
  $name1 = PLAYERS[$p1]['name'];
  $name2 = PLAYERS[$p2]['name'];
  return sprintf("%s/%s-%s", $dir, $name1, $name2);
}
