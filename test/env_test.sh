#!/bin/bash

func=$(find . -name "assert.sh")
source $func

assert env
assert env -
assert env -----
assert env aaa
assert env env
