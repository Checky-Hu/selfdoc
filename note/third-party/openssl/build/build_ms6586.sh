#!/bin/bash

# Set temp toolchain.
export PATH=${PATH}:${HOME}/Templates/toolchains/ms6586/arm-2014.05/bin
export CC=arm-none-linux-gnueabi-gcc
export CXX=arm-none-linux-gnueabi-g++

./Configure --prefix=/home/checky/Public/ms6586-buildroot/ linux-armv4
make -j8
make install
