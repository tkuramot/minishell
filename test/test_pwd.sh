#!/bin/bash

func=$(find . -name "assert.sh")
source $func

assert_pwd ''
assert_pwd 'aaaaaaa'
assert_pwd 'aaa bbb ccc'
assert_pwd '  aaa   bbb    ccc '
#assert_pwd '-nnnnan'
#assert_pwd '-a'
#assert_pwd '---------n'
assert_pwd '--'
assert_pwd '-'
