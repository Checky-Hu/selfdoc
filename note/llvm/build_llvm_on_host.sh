#!/bin/sh
cd build

export TEMP_PREFIX_DIR="/home/checky/Templates/prefix"

#-DCLANG_ANALYZER_Z3_INSTALL_DIR=${TEMP_PREFIX_DIR}
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${TEMP_PREFIX_DIR} \
  ../llvm

unset TEMP_PREFIX_DIR

cd ..
