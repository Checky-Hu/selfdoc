#!/bin/bash

# Set temp toolchain.
export TMP_TOOLCHAIN_ROOT=${HOME}/Templates/toolchains/ms6586/arm-2014.05
export TMP_OLD_PATH=${PATH}
export PATH=${PATH}:${TMP_TOOLCHAIN_ROOT}/bin
export TARGET_CC=arm-none-linux-gnueabi-gcc
export TARGET_CXX=arm-none-linux-gnueabi-g++

# Set build root.
export HOST_BUILD_ROOT=${HOME}/Public/buildroot
export TARGET_BUILD_ROOT=${HOME}/Public/ms6586-buildroot
export ARMV7_UNKNOWN_LINUX_GNUEABI_OPENSSL_DIR=${TARGET_BUILD_ROOT}
export OPENSSL_DIR=${HOST_BUILD_ROOT}
