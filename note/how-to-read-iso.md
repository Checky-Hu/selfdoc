how to read iso
======

```shell
mount plan9.iso /home/checky/Documents/os/plan9/plan9/
```

Result by "df -Th":

```
Filesystem                      Type      Size  Used Avail Use% Mounted on
udev                            devtmpfs  3.8G     0  3.8G   0% /dev
tmpfs                           tmpfs     777M  9.2M  768M   2% /run
/dev/mapper/checky--hu--vg-root ext4       23G  3.7G   18G  17% /
tmpfs                           tmpfs     3.8G   11M  3.8G   1% /dev/shm
tmpfs                           tmpfs     5.0M  4.0K  5.0M   1% /run/lock
tmpfs                           tmpfs     3.8G     0  3.8G   0% /sys/fs/cgroup
/dev/sda1                       ext2      236M   37M  187M  17% /boot
/dev/mapper/checky--hu--vg-var  ext4      9.2G  726M  8.0G   9% /var
/dev/mapper/checky--hu--vg-tmp  ext4      1.8G  5.7M  1.7G   1% /tmp
/dev/mapper/checky--hu--vg-home ext4      879G   41G  793G   5% /home
tmpfs                           tmpfs     777M   12K  777M   1% /run/user/1000
/dev/loop0                      iso9660   287M  287M     0 100% /home/checky/Documents/os/plan9/plan9
```

then feel free to do anything.
