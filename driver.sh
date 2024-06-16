#!/bin/bash

PATH_TO_TWOGTP="/path/to/pentobi/twogtp/twogtp"
PATH_TO_PENTOBI="/path/to/pentobi_gtp/pentobi-gtp"
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PATH_TO_US="$SCRIPT_DIR/byrg"

rm -rf output.dat output.blksgf

# Four player
$PATH_TO_TWOGTP \
  --blue $PATH_TO_US \
  --yellow $PATH_TO_PENTOBI \
  --red $PATH_TO_PENTOBI \
  --green $PATH_TO_PENTOBI \
  -g classic

# Two player
# $PATH_TO_TWOGTP \
#   --black $PATH_TO_US \
#   --white $PATH_TO_PENTOBI \
#   -g duo
