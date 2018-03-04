#!/bin/sh
#how to use shell array
array=()
array[0]=""
array[1]="hello"
array[2]=123
for var in ${array[*]}
do
  echo ${var}
done
