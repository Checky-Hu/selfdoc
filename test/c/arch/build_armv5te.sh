#!/bin/sh
if [ ! -d out ];then
    mkdir out
fi

arm-none-linux-gnueabi-gcc -march=armv5te -Wall -g main.c -o out/armv5te_main
