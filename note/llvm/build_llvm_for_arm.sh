#!/bin/sh
cd arm-build

export TEMP_CUR_DIR=`pwd`
export TEMP_HOST_PREFIX_DIR="/home/checky/Templates/prefix"
export TEMP_ARM_PREFIX_DIR="/home/checky/Templates/arm-prefix"
export PATH="${PATH}:/home/checky/Public/opensource/flutter/depot_tools:${TEMP_HOST_PREFIX_DIR}/bin"

export TEMP_TOOLCHAIN_ROOT_DIR="/home/checky/Templates/toolchains/nt563-sdk/gcc-linaro-arm-linux-gnueabihf-4.9-2014.08_linux"
export TEMP_TOOLCHAIN_TRIPLE="arm-linux-gnueabihf"
export CC="clang"
export CXX="clang++"

cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${TEMP_ARM_PREFIX_DIR} \
  -DCMAKE_CROSSCOMPILING=True -DCMAKE_SYSTEM_NAME=Linux -DCMAKE_SYSTEM_PROCESSOR=arm \
  -DCMAKE_FIND_ROOT_PATH=${TEMP_ARM_PREFIX_DIR} -DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER \
  -DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY \
  -DLLVM_TABLEGEN=${TEMP_HOST_PREFIX_DIR}/bin/llvm-tblgen \
  -DCLANG_TABLEGEN=${TEMP_CUR_DIR}/../build/bin/clang-tblgen \
  -DLLVM_DEFAULT_TARGET_TRIPLE=${TEMP_TOOLCHAIN_TRIPLE} \
  -DLLVM_TARGET_ARCH=ARM -DLLVM_TARGETS_TO_BUILD=ARM \
  -DCMAKE_C_FLAGS="-march=armv7-a -mcpu=cortex-a9 -mfpu=vfpv3-d16 -mfloat-abi=hard --target=${TEMP_TOOLCHAIN_TRIPLE} --gcc-toolchain=${TEMP_TOOLCHAIN_ROOT_DIR} --sysroot=${TEMP_TOOLCHAIN_ROOT_DIR}/${TEMP_TOOLCHAIN_TRIPLE}/libc -I${TEMP_ARM_PREFIX_DIR}/include -v" \
  -DCMAKE_CXX_FLAGS="-march=armv7-a -mcpu=cortex-a9 -mfpu=vfpv3-d16 -mfloat-abi=hard --target=${TEMP_TOOLCHAIN_TRIPLE} --gcc-toolchain=${TEMP_TOOLCHAIN_ROOT_DIR} --sysroot=${TEMP_TOOLCHAIN_ROOT_DIR}/${TEMP_TOOLCHAIN_TRIPLE}/libc -I${TEMP_ARM_PREFIX_DIR}/include -v" \
  -DCMAKE_ASM_FLAGS="-march=armv7-a -mcpu=cortex-a9 -mfpu=vfpv3-d16 -mfloat-abi=hard --target=${TEMP_TOOLCHAIN_TRIPLE} --gcc-toolchain=${TEMP_TOOLCHAIN_ROOT_DIR} --sysroot=${TEMP_TOOLCHAIN_ROOT_DIR}/${TEMP_TOOLCHAIN_TRIPLE}/libc -v" \
  ../llvm

unset TEMP_TOOLCHAIN_ROOT_DIR
unset TEMP_TOOLCHAIN_TRIPLE
unset CC
unset CXX

unset TEMP_CUR_DIR
unset TEMP_HOST_PREFIX_DIR
unset TEMP_ARM_PREFIX_DIR

cd ..
