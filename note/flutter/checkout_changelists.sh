#!/bin/sh
#checkout changelists of the flutter project
git_paths=`find engine -name ".git"`

git_paths_array=(${git_paths})
for git_path in ${git_paths_array[*]}
do
  cd ${git_path}/../
  modified_files=`git status | grep 'modified:' | awk '{print $2}'`
  if [ "x${modified_files}" != "x" ]
  then
    echo -e "\n"${git_path}":"
    modified_files_array=(${modified_files})
    for modified_file in ${modified_files_array[*]}
    do
      echo ${modified_file}
    done
  fi
  cd - > /dev/null
done
