#!/bin/bash

func=$(find . -name "assert.sh")
source $func

assert exit
assert exit 0
assert exit 0a
assert exit 120
assert exit 256
assert exit 512
assert exit 0a 00
assert exit 120 312
assert exit 256 fa
assert exit 512 99
assert exit 2147483647
assert exit -2147483648
assert exit -2
assert exit exit
