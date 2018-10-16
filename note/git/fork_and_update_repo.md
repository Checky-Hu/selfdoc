fork and update repo by git
=======

1. fork repo;
2. clone your own repo to local and show remote branch;
```shell
git clone own-repo
git remote -v
```
3. add the source repo to remote branch as upstream;
```shell
git remote add upstream src-repo
git remote -v
```
4. update local upstream branch;
```shell
git fetch upstream
```
5. checkout one of your own local branch that you want to update(master);
```shell
git checkout master
```
6. merge one of local upstream branch(master) to your own local branch;
```shell
git merge upstream/master
# use upstream to override your own changes when there are conflicts
git merge -X theirs upstream/master
```
7. push your own local branch changes to remote;
```shell
git push
```
