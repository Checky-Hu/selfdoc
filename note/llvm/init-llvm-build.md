Init LLVM Build
=======

1. prebuild `libxml2/z3/zlib` for LLVM;
2. check out the source code of LLVM:

```shell
mkdir clang-llvm
cd clang-llvm

# check out llvm
svn checkout http://llvm.org/svn/llvm-project/llvm/trunk llvm

# check out clang
cd llvm/tools
svn checkout http://llvm.org/svn/llvm-project/cfe/trunk clang
cd ../..

# check out clang extra
cd llvm/tools/clang/tools
svn checkout http://llvm.org/svn/llvm-project/clang-tools-extra/trunk extra
cd ../../../..

# check out lld(this step can be skipped since we don't use lld)
cd llvm/tools
svn checkout http://llvm.org/svn/llvm-project/lld/trunk lld
cd ../..

# check out compiler-rt
cd llvm/projects
svn checkout http://llvm.org/svn/llvm-project/compiler-rt/trunk compiler-rt
cd ../..

# check out libcxxabi
cd llvm/projects
svn checkout http://llvm.org/svn/llvm-project/libcxxabi/trunk libcxxabi
cd ../..

# check out libcxx
cd llvm/projects
svn checkout http://llvm.org/svn/llvm-project/libcxx/trunk libcxx
cd ../..
```

3. use the script `build_llvm_on_host.sh` or `build_llvm_for_arm.sh` to start build.
