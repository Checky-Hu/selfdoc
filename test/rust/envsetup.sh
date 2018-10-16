#!/bin/bash
tmpcmd=`cat ${HOME}/.cargo/env` && eval ${tmpcmd}
echo ${PATH}

rustc --version
cargo --version
