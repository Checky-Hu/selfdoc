sudo cmd
======

- install sudo command: `apt-get install sudo`
- check /etc/sudoers file to see who can use sudo:
```shell
# usually, all the users belongs to sudo group has the sudo permission.
cat /etc/sudoers
```
- check whether current user belongs to sudo group:
```shell
cat /etc/group | grep ${USER_NAME}
# or
groups ${USER_NAME}
```
- add user to sudo group and then we can use sudo **after reboot**:
```shell
# -a means append user to new group but not change it's main group.
# -G means which group to append.
usermod -a -G sudo ${USER_NAME}
```
