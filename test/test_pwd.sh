#!/bin/bash

func=$(find . -name "assert.sh")
source $func

assert
assert aaaaaaa
assert aaa bbb ccc
assert   aaa   bbb    ccc
#asserd -nnnnan
#asserd -a
#asserd ---------n
assert --
assert -
