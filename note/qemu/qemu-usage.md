how to use qemu
======

1. create c source file: `hello.c`
2. use arm toolchain to compile:
```shell
../../../toolchains/gcc-linaro-arm-linux-gnueabihf-4.9-2014.08_linux/bin/arm-linux-gnueabihf-gcc -Wall -g hello.c -o out/hello
```
3. use qemu to execute:
```shell
qemu-arm out/hello
```
4. if there are errors, try to set the QEMU_LD_PATH:
```shell
qemu-arm -help
qemu-arm -L ../../../toolchains/gcc-linaro-arm-linux-gnueabihf-4.9-2014.08_linux/arm-linux-gnueabihf/libc/ out/hello
```
