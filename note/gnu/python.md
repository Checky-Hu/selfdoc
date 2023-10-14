python commands
======

## pyenv
```shell
# install python of target version
pyenv install ${PYTHON_VERSION}

# create virtualenv of target python
pyenv virtualenv ${PYTHON_VERSION} ${ENV_NAME}

# enter target env
pyenv activate ${ENV_NAME}

# exit current env
source deactivate

# uninstall target env
pyenv uninstall ${ENV_NAME}

# show all virtualenv
pyenv virtualenvs
```

