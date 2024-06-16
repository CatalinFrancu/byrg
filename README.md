# byrg

Byrg is a Blokus engine compatible with [Pentobi GTP](https://github.com/enz/pentobi/blob/master/pentobi_gtp/Pentobi-GTP.md). It can play the Classic and Duo variants.

Byrg has no GUI of its own and thus cannot easily play against human opponents. It is intended for use with Pentobi's [twogtp](https://github.com/enz/pentobi/tree/master/twogtp). My own patch of [twogtp](https://github.com/CatalinFrancu/pentobi/tree/master/twogtp) also works with four engines.

At the end of the game, twogtp outputs a Blokus game file, which you can open and inspect using Pentobi.

### Building instructions

```bash
cmake .
make
```

### Usage instructions

See [driver.sh](driver.sh) for an example of using twogtp to orchestrate a game.
