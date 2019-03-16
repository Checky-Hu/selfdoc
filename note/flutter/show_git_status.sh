#!/bin/sh
#show git status of the flutter project
git_paths=`find engine -name ".git"`

git_paths_array=(${git_paths})
for git_path in ${git_paths_array[*]}
do
  echo -e "\n"${git_path}":"
  cd ${git_path}/../
  git status
  cd - > /dev/null
done
