#!/bin/sh
clang++ -std=c++17 -stdlib=libc++ -Wall cpp14_support_test.cc -nostdinc++ -isysroot /home/checky/Templates/prefix/ -iwithsysroot /include/c++/v1/ -Wl,-rpath=/home/checky/Templates/prefix/lib/ -o ../out/clang_cpp14_support_test
