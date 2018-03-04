#!/bin/sh
#how to use let
i=0
while [ ${i} -lt 5 ]
do
  let i=${i}+1
  echo ${i}
done
