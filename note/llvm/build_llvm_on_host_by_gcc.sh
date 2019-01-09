#!/bin/sh
cd build

export TEMP_PREFIX_DIR="/home/checky/Templates/prefix"

#-DLIBCXXABI_USE_COMPILER_RT=ON -DLIBCXX_USE_COMPILER_RT=ON \
#  Disable because both GCC and Clang on linux doesn't support "-rtlib=compiler-rt" option.
#  We must link libc++ and libc++abi with libgcc.
#-DCLANG_ANALYZER_Z3_INSTALL_DIR=${TEMP_PREFIX_DIR} \
#  Useless since cmake will find Z3 in CMAKE_INSTALL_PREFIX already.
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${TEMP_PREFIX_DIR} \
  ../llvm

unset TEMP_PREFIX_DIR

cd ..
