#!/bin/bash
gcc -Wall -g dbus_app.c -I/usr/include/dbus-1.0/ -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include/ -L/usr/lib/x86_64-linux-gnu/ -ldbus-1 -o ../out/dbus_app
