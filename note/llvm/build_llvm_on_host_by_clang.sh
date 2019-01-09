#!/bin/sh
cd build-by-clang

export TEMP_PREFIX_DIR="/home/checky/Templates/prefix"
export PATH="${PATH}:${TEMP_PREFIX_DIR}/bin"

export CC="clang"
export CXX="clang++"

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${TEMP_PREFIX_DIR} \
  ../llvm

unset TEMP_PREFIX_DIR
unset CC
unset CXX

cd ..
