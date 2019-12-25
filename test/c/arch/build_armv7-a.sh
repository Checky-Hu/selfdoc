#!/bin/sh
if [ ! -d out ];then
    mkdir out
fi

arm-none-linux-gnueabi-gcc -march=armv7-a -Wall -g main.c -o out/armv7-a_main
