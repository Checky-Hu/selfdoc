#!/bin/sh
clang++ -std=c++17 -stdlib=libc++ -Wall cpp14_support_test.cc -nostdinc++ -isystem /home/checky/Templates/prefix/include/c++/v1/ -lc++ -Wl,-rpath=/home/checky/Templates/prefix/lib/ -o out/clang_cpp14_support_test 
