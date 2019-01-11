#!/bin/sh
if [ x${TMP_TARGET_TRIPLE} == x ]
then
  TMP_TARGET_TRIPLE="arm-linux-gnueabihf"
  TMP_TARGET_TOOLCHAIN="/home/checky/Templates/toolchains/nt563-sdk/gcc-linaro-arm-linux-gnueabihf-4.9-2014.08_linux" 

  cd engine/src/buildtools
  export PATH="${PATH}:`pwd`"
  cd -
fi
echo ${PATH}

if [ "$1" == host ]
then
  ./engine/src/flutter/tools/gn --unoptimized --runtime-mode=debug
elif [ "$1" == android ]
then
  ./engine/src/flutter/tools/gn --unoptimized --runtime-mode=debug --android
elif [ "$1" == sita ]
then
  if [ "$2" == cxx ]
  then
    ./engine/src/flutter/tools/gn --unoptimized --runtime-mode=debug --sita --sita-cpu=arm --sita-prebuilt=/home/checky/Templates/prefix/bin --sita-use-vfp --arm-float-abi=hard --target-sysroot=${TMP_TARGET_TOOLCHAIN}/${TMP_TARGET_TRIPLE}/libc --target-toolchain=${TMP_TARGET_TOOLCHAIN} --target-triple=${TMP_TARGET_TRIPLE} --embedder-for-target
  else
    ./engine/src/flutter/tools/gn --unoptimized --runtime-mode=debug --sita --sita-cpu=arm --sita-use-vfp --arm-float-abi=hard --target-sysroot=${TMP_TARGET_TOOLCHAIN}/${TMP_TARGET_TRIPLE}/libc --target-toolchain=${TMP_TARGET_TOOLCHAIN} --target-triple=${TMP_TARGET_TRIPLE} --embedder-for-target
  fi
else
  echo "unknown platform"
fi
