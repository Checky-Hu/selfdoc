zypper cmd
========

- update package list: `zypper update`
- install new package: `zypper install ${package-name}`
- remove a package:
```shell
zypper remove --details ${package-name}
```
- remove a package and it's dependency:
```shell
zypper remove -u --details ${package-name}
```
- upgrade all installed packages: `zypper update`
- upgrade system version: `zypper dist-upgrade`
- search package in package list:
```shell
zypper search ${package-name}
```
- show package info: `zypper info ${package-name}`
- uninstall old kernel:
```shell
# show installed kernel image
rpm -qa | grep -i kernel
# uninstall old kernel
rpm -e kernel-XXX
```
