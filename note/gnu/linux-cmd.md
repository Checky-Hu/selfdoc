simple commands of linux
======

## show linux kernel version
```shell
# method 1
uname -a
# method 2
cat /proc/version
```

## show linux release version
```
lsb_release -a
```

## search symbol in binary(executable file or library)
```shell
# method 1
nm -D ${FILE_NAME} | grep ${SYMBOL}
# method 2
objdump -t ${FILE_NAME} | grep ${SYMBOL}
```

## show disk space
```shell
# show current directory size
du -sh
# show current disk usage of each partition
df -lh
```

## show link dependency of library
```shell
# on x86
ldd ${LIB_NAME}
# on arm
arm-linux-gnueabihf-readelf -d ${LIB_NAME}
```

## other commands

### tar
```shell
# 'z' means 'tar.gz', use 'tar --help' to see more about 'tar.xz' and 'tar.bz2'
# 'c' means compress
tar -zcvf ${TARGET_FILE} ${SOURCE_FILE}
# 'x' means uncompress
tar -zxvf ${PACK_FILE}
```

### test
```shell
# judge and return whether the expression is true or false
test ${EXPRESSION}
```

### patch
```shell
# create patch file
diff -uparN a.c new_a.c > a.patch
# generate target file
patch -p1 < a.patch
```

### hexdump
```shell
# show binary data
hexdump -C ${BIN_DATA}
```

### gcc
```shell
# use 'pkg-config' to solve the include and link problems like autoconf & libtool
gcc -o ${PROGRAM} ${SOURCE} ``pkg-config --cflags --libs libinput``
```
