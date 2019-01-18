#!/bin/sh

if [ x${TMP_OUT_PATH} == x ]
then
  TMP_PREBUILT_PATH="/home/checky/Public/opensource/flutter/engine/src/out"
  TMP_TOOLCHAIN_PATH="/home/checky/Templates/toolchains/nt563-sdk/gcc-linaro-arm-linux-gnueabihf-4.9-2014.08_linux/bin"
  export PATH="${PATH}:${TMP_PREBUILT_PATH}/sita_debug_unopt/clang_x86:${TMP_PREBUILT_PATH}/host_debug_unopt:${TMP_TOOLCHAIN_PATH}"
  TMP_OUT_PATH="out"
  TMP_FLUTTER_PATH="/home/checky/Public/opensource/flutter/flutter"
fi

if [ $1 == 1 ]
then
dart ${TMP_PREBUILT_PATH}/host_debug_unopt/frontend_server.dart.snapshot \
  --sdk-root ${TMP_PREBUILT_PATH}/sita_debug_unopt/flutter_patched_sdk \
  --strong --target=flutter \
  --aot --tfa -Ddart.vm.product=true \
  --packages=../example/.packages \
  --output-dill=${TMP_OUT_PATH}/app.dill.track.dill \
  --depfile=${TMP_OUT_PATH}/kernel_compile.d \
  ../example/lib/main.dart
fi

if [ $1 == 2 ]
then
gen_snapshot --deterministic --snapshot_kind=app-aot-assembly --assembly=${TMP_OUT_PATH}/snapshot_assembly.S \
  --no-use-integer-division --causal_async_stacks \
  --packages=../example/.packages ${TMP_OUT_PATH}/app.dill.track.dill
fi

if [ $1 == 3 ]
then
arm-linux-gnueabihf-gcc -shared -o ${TMP_OUT_PATH}/app.so ${TMP_OUT_PATH}/snapshot_assembly.S
fi
