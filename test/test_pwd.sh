#!/bin/bash

func=$(find . -name "assert.sh")
source $func

assert pwd
assert pwd aaaaaaa
assert pwd aaa bbb ccc
assert pwd   aaa   bbb    ccc
#asserd pwd -nnnnan
#asserd pwd -a
#asserd pwd ---------n
assert pwd --
assert pwd -
