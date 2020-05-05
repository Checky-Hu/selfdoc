#!/bin/bash
./Configure --prefix=/home/checky/Public/buildroot/ linux-x86_64
make -j8
make install
