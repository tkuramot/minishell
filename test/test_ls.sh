#!/bin/bash

func=$(find . -name "assert.sh")
source $func

assert ls
assert ls src
assert ls ./src
assert ls src obj
assert ls none
assert ls Makefile
assert ls ~
assert ls /
assert ls src obj
assert ls src obj none
assert ls none src obj
assert ls -
assert ls -----
