install os
=========

1. make usb as a boot device:
```shell
umount /dev/sdb1
dd if=./debian-9.80-release-desktop-amd64.iso of=/dev/sdb1
```
2. enter bios mode when power on: `Press F10/F2/DELETE/ESC`
3. system partition: `boot;/;/var;swap;/tmp;/home;`