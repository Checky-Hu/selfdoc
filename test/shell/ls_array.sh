#!/bin/sh
#how to use result value of ls cmd
result=`ls | grep sh`
echo ${result}
:<<!
OLD_IFS=${IFS}
IFS=','
echo do something
IFS=${OLD_IFS}
!
array=(${result})
for var in ${array[*]}
do
  echo ${var}
done
