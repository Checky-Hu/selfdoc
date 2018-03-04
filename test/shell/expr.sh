#!/bin/sh
#how to use expr
i=0
while [ ${i} -lt 5 ]
do
  i=`expr ${i} + 1`
  echo ${i}
done
