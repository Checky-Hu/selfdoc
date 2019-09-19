#!/bin/sh
if [ ! -d out ];then
    mkdir out
fi

g++ -Wall -g main.cc thread.cc fruit.cc -lpthread -o out/main
