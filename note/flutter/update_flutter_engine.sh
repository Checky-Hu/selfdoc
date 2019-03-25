#!/bin/sh
cd depot_tools
export PATH="${PATH}:`pwd`"
echo ${PATH}
cd ../engine
# gclient sync
