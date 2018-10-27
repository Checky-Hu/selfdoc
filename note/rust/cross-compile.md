cross compile of rust
=====

## add platform depends rust std lib
1. show all the supported platforms:
```shell
rustup target list
```
2. add target platform's rust std lib:
```shell
rustup target add ${TARGET_NAME}
```

## use rustc to compile:
```shell
#see ${root}/test/rust/hello/build.sh for details.
rustc -C linker=${TARGET_TOOLCHAIN_NAME} --target=${TARGET_NAME} main.rs -o main
```

## use cargo build:
```shell
#add cargo config file(~/.cargo/config) like below.
#see ${root}/self-conf/rust/config for details.
[target.${TARGET_NAME}]
linker = ${TARGET_TOOLCHAIN_NAME}

#cargo build
cargo build --target=${TARGET_NAME}
```

## other
1. guessing_game doesn't work on NT563 by cross compiling. It fails at `extern crate rand`;
2. it's unknown whether prebuilt rust std lib on target platform can fit all cross compile toolchains.
