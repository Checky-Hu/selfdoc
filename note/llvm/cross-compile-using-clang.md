Cross Compile using Clang
========

## Option
### using `--target <triple>`
`<triple>` means: `<arch><sub>-<vendor>-<sys>-<abi>`
- arch: `x86_64|i386|arm|thumbs|mips`
- sub(for arm): `v5|v6m|v7a|v7m`
- vendor: `pc|apple|ibm`
- sys: `none|linux|win32|darwin`
- abi: `eabi|gnu|android|elf`

`<triple>` should be the cross compile toolchain's name.

### compile flags
- set cpu: `-mcpu=<cpu-name>`
- set fpu(sse3|neon): `-mfpu=<fpu-name>`
- set float abi(soft|hard): `-mfloat-abi=<fabi>`

use `<triple>-gcc -v` to show the specific value of those parameters above.

### paths for header files and libraries
- use `--sysroot=<root_path>` and `-I -L` options

`<root_path>` should point to the platform's root which contains `etc|lib|usr` in cross compile toolchain's directory. it should be `<toolchain_path>/<triple>/libc`.

- use `--gcc-toolchain=<toolchain_path>` indicate linker path

`<toolchain_path>` should be the cross compile toolchain's directory.
