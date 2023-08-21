#!/bin/bash

src=$(find . -name "assert.sh")
source $src

# without option
assert_echo ''
assert_echo 'aaaaaaa'
assert_echo 'aaa bbb ccc'
assert_echo '  aaa   bbb    ccc '
assert_echo '-nnnnan'
assert_echo '-a'
assert_echo '---------n'
assert_echo '--'
assert_echo '-'

# with option
assert_echo '-n'
assert_echo '-nnnnn'
assert_echo '-nnnnnnnn -n'
assert_echo '-nnnnnnnn -nnnnn'
assert_echo '-nnnnnnnn -na'
assert_echo '-nnnnnnnn -a'
assert_echo '-n 123'
assert_echo '-nnnnnnnn -n 1 2 3'
assert_echo '-nnnnnnnn -nnnnn 1 2 3'
assert_echo '-nnnnnnnn -na 1 2 3'
assert_echo '-nnnnnnnn -a 1 2 3'
