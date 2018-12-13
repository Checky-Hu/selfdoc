#!/bin/sh
export CROSS_ROOT="/home/checky/Templates/toolchains/nt563-sdk/gcc-linaro-arm-linux-gnueabihf-4.9-2014.08_linux"
export CROSS_TRIPLE="arm-linux-gnueabihf"

# add '-fuse-ld=lld' option to enable llvm-lld(speed up linking?)
clang++ --target=${CROSS_TRIPLE} -mcpu=cortex-a9 -mfpu=vfpv3-d16 -mfloat-abi=hard \
  --gcc-toolchain=${CROSS_ROOT} \
  --sysroot=${CROSS_ROOT}/${CROSS_TRIPLE}/libc \
  -v -std=c++11 -Wall ../std_vector_init.cc -o ../out/arm_clang_std_vector_init

unset CROSS_ROOT
unset CROSS_TRIPLE
