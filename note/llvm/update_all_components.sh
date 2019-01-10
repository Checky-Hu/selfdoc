#!/bin/sh
#update all components of the clang/llvm project
svn_paths=`find llvm -name ".svn"`

svn_paths_array=(${svn_paths})
for svn_path in ${svn_paths_array[*]}
do
  echo ${svn_path}":"
  cd ${svn_path}/../
  svn up
  echo -e "update "${svn_path}"\n"
  cd - > /dev/null
done
