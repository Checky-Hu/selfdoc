#!/bin/bash

# Clear temp toolchain.
unset TMP_TOOLCHAIN_ROOT
export PATH=${TMP_OLD_PATH}
unset TMP_OLD_PATH
unset TARGET_CC
unset TARGET_CXX

# Clear build root.
unset HOST_BUILD_ROOT
unset TARGET_BUILD_ROOT
unset ARMV7_UNKNOWN_LINUX_GNUEABI_OPENSSL_DIR
unset OPENSSL_DIR
