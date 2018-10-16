git tag cmd
=======

1. create local tag:
```shell
git tag -a tagname -m "message"
```
2. delete local tag:
```shell
git tag -d tagname
```
3. push tag to remote origin:
```shell
git push origin refs/tags/src-tagname:refs/tags/dst-tagname
```
4. add tag to remote origin(ignore dst param in 3):
```shell
git push origin tagname
```
5. delete tag from remote origin(ignore src param in 3):
```shell
git push origin :refs/tags/dst-tagname
```
