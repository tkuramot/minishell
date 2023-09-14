#!/bin/bash

func=$(find . -name "assert.sh")
source $func

echo
echo ENV TEST

assert env
assert env -
assert env -----
assert env aaa
assert env env
