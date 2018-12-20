Cross Compile LLVM(for Arm)
=======

## Cmake Options
### common cmake options
- `-DCMAKE_CROSSCOMPILING=True`
- `-DCMAKE_INSTALL_PREFIX=<install-dir>`
- `-DLLVM_TABLEGEN=<path-to-host-bin>/llvm-tblgen`
- `-DCLANG_TABLEGEN=<path-to-host-bin>/clang-tblgen`
- `-DLLVM_DEFAULT_TARGET_TRIPLE=arm-linux-gnueabi`
- `-DLLVM_TARGET_ARCH=ARM`
- `-DLLVM_TARGETS_TO_BUILD=ARM`

### options when using clang as cross compiler
`-DCMAKE_ASM_FLAGS=<-mcpu=* -mfpu=* -mfloat-abi=* --target=* --gcc-toolchain=* --sysroot=*>`

`-DCMAKE_C_FLAGS=<-mcpu=* -mfpu=* -mfloat-abi=* --target=* --gcc-toolchain=* --sysroot=* -I* -L*>`

`-DCMAKE_CXX_FLAGS=<-mcpu=* -mfpu=* -mfloat-abi=* --target=* --gcc-toolchain=* --sysroot=* -I* -L*>`

The specific values of `*` have been explained in `./cross-compile-using-clang.md`. See `../../test/cpp/cpp14/clang_arm_cxx11_build.sh` as an example.

More options see `./build_llvm_for_arm.sh`.

### no extra options when using gcc as cross compiler
Build success when using gcc 6.3.0 but failed in gcc 4.9.2(personal experience).
