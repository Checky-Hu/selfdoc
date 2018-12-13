#!/bin/sh
clang++ -std=c++17 -stdlib=libc++ -Wall cpp14_support_test.cc -nostdinc++ -cxx-isystem /home/checky/Templates/prefix/include/c++/v1/ -Wl,-rpath=/home/checky/Templates/prefix/lib/ -fuse-ld=lld -v -o ../out/clang_cpp14_support_test
