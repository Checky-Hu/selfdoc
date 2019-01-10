#!/bin/sh
#checkout changelists of the clang/llvm project
svn_paths=`find llvm -name ".svn"`

svn_paths_array=(${svn_paths})
for svn_path in ${svn_paths_array[*]}
do
  echo ${svn_path}":"
  cd ${svn_path}/../
  svn st -q
  echo -e "\n"
  cd - > /dev/null
done
