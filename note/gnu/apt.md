apt cmd
========

- update package list: `apt-get update`
- install new package: `apt-get install packagename`
- remove a package:
```shell
# keep config files
apt-get remove packagename
# no config files any more
apt-get remove --purge packagename
```
- remove a package and it's dependency:
```shell
# keep config files
apt-get autoremove packagename
# no config files any more
apt-get autoremove --purge packagename
```
- remove backup of uninstalled package: `apt-get autoclean`
- remove backup of installed & uninstalled package: `apt-get clean`
- upgrade all installed packages: `apt-get upgrade`
- upgrade system version: `apt-get dist-upgrade`
- search package in package list:
```shell
apt-cache search string
# or
dpkg -l string-pattern
```
- show package info: `apt-cache showpkg packagename`
- show the file belongs to which installed package: `dpkg -S file`
- show all files that included in package: `dpkg -L packagename`
- add source to source list and install(install WIFI driver as example):
```shell
vim /etc/apt/sources.list
deb http://httpredir.debian.org/debian/ jessie main contrib non-free
# different driver depends on WIFI hardware
apt-get install firmware-*
```
- uninstall old kernel:
```shell
# show installed kernel image
dpkg --get-selections | grep linux
# uninstall old kernel
dpkg --purge --force-remove-essential linux-image-XXX
```
