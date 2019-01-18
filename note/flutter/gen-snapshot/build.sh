#!/bin/sh

if [ x"${TMP_TOOLCHAIN_PATH}" == x ]
then
  TMP_TOOLCHAIN_PATH="/home/checky/Templates/toolchains/nt563-sdk/gcc-linaro-arm-linux-gnueabihf-4.9-2014.08_linux"
  TMP_TOOLCHAIN_TRIPLE="arm-linux-gnueabihf"
  TMP_FLUTTER_PREBUILT="/home/checky/Public/opensource/flutter/engine/src/out/sita_debug_unopt"
  TMP_PLATFORM_PORTING="/home/checky/Templates/porting/nt563linux"
  export PATH="${PATH}:${TMP_TOOLCHAIN_PATH}/bin"
fi

arm-linux-gnueabihf-g++ -I${TMP_FLUTTER_PREBUILT} -I${TMP_PLATFORM_PORTING}/include/khronos \
  -L${TMP_PLATFORM_PORTING}/lib/ -L${TMP_FLUTTER_PREBUILT} \
  -lEGL -lGLESv2 -ldl -lflutter_sita \
  -Wl,--allow-shlib-undefined -Wall -g main.cc -std=c++11 -o main
