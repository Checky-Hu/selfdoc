init repo with local project by git
=======

1. find local project and init as git repo;
```shell
git init
```
2. create remote repo on git server(Github or Gitee);
3. add remote repo url to local repo;
```shell
git remote add origin ${remote-repo-url}
```
4. sync local repo with master branch of remote repo;
```shell
git pull origin master:master
```
5. push local branch to remote repo if need;
```shell
git push -u origin master
```
6. add local files and commit and push to remote;
```shell
# add all local files and commit.
git add -A
git commit -m '${comment}'
# push to master branch of origin.
git push --set-upstream origin master
```

