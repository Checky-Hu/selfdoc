#!/bin/sh
export CROSS_ROOT="/home/checky/Templates/toolchains/nt563-sdk/gcc-linaro-arm-linux-gnueabihf-4.9-2014.08_linux"
export CROSS_TRIPLE="arm-linux-gnueabihf"
export CROSS_PREBUILT="/home/checky/Templates/arm-prefix"

# add '-fuse-ld=lld' option to enable llvm-lld(speed up linking?)
clang++ --target=${CROSS_TRIPLE} -mcpu=cortex-a9 -mfpu=vfpv3-d16 -mfloat-abi=hard \
  --gcc-toolchain=${CROSS_ROOT} \
  --sysroot=${CROSS_ROOT}/${CROSS_TRIPLE}/libc \
  -nostdinc++ -cxx-isystem ${CROSS_PREBUILT}/include/c++/v1/ \
  -L${CROSS_PREBUILT}/lib \
  -Wl,-rpath=/data/clang \
  -v -std=c++17 -stdlib=libc++ -Wall cpp14_support_test.cc -o ../out/arm_clang_cpp14_support_test

unset CROSS_ROOT
unset CROSS_TRIPLE
unset CROSS_PREBUILT
