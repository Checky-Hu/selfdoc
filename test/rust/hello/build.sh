#!/bin/bash
rustc -C linker=arm-linux-gnueabihf-gcc --target=arm-unknown-linux-gnueabihf hello.rs -o ../out/nt563-hello
